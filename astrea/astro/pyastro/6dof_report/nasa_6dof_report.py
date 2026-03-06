#!/usr/bin/env python3

"""
NASA 6DOF Orbital Test Results Report Generator

This script automatically generates comprehensive reports from the NASA 6DOF 
orbital checkcase test results, including performance metrics, comparison plots,
and manual annotations.

An AI wrote this file.
"""

import os
import sys
import pandas as pd
import numpy as np
from pathlib import Path
from datetime import datetime
from typing import Dict, List, Optional, Tuple
import base64
import argparse
import json
import webbrowser

try:
    import matplotlib.pyplot as plt
    import matplotlib.image as mpimg
    MATPLOTLIB_AVAILABLE = True
except ImportError:
    MATPLOTLIB_AVAILABLE = False
    print("Warning: matplotlib not available. Some plotting features may be limited.")


class NASA6DOFReportGenerator:
    """Class for generating comprehensive reports from NASA 6DOF orbital test results."""
    
    def __init__(self, results_dir: str = None):
        """
        Initialize the report generator.
        
        Args:
            results_dir: Path to the orbital results directory
        """
        if results_dir is None:
            # Default to the standard location
            self.results_dir = Path(__file__).parent.parent.parent / "tests" / "nasa_6dof_checkcases" / "orbital" / "results"
        else:
            self.results_dir = Path(results_dir)
            
        if not self.results_dir.exists():
            raise FileNotFoundError(f"Results directory not found: {self.results_dir}")
            
        self.orbit_tests = self._discover_orbit_tests()
        self.report_data = {}
        
    def _discover_orbit_tests(self) -> List[str]:
        """Discover all available orbit test directories."""
        orbit_dirs = []
        for item in self.results_dir.iterdir():
            if item.is_dir() and item.name.startswith("Orbit_"):
                orbit_dirs.append(item.name)
        return sorted(orbit_dirs)
    
    def load_test_results(self, orbit_name: str) -> Dict:
        """
        Load test results for a specific orbit test.
        
        Args:
            orbit_name: Name of the orbit test (e.g., 'Orbit_02')
            
        Returns:
            Dictionary containing test data
        """
        orbit_path = self.results_dir / orbit_name
        if not orbit_path.exists():
            raise FileNotFoundError(f"Orbit test directory not found: {orbit_path}")
            
        test_data = {
            'orbit_name': orbit_name,
            'path': orbit_path,
            'summary_data': None,
            'images': {},
            'checkcases': {}
        }
        
        # Load main summary CSV if it exists
        summary_file = orbit_path / "summary.csv"
        if summary_file.exists():
            try:
                test_data['summary_data'] = pd.read_csv(summary_file)
                # Clean column names (remove leading/trailing whitespace)
                if test_data['summary_data'] is not None:
                    test_data['summary_data'].columns = test_data['summary_data'].columns.str.strip()
            except Exception as e:
                print(f"Warning: Could not load summary CSV for {orbit_name}: {e}")
                test_data['summary_data'] = None
                
        # Load main comparison images
        for img_file in ["trajectory_comparison.png", "orbital_elements_comparison.png"]:
            img_path = orbit_path / img_file
            if img_path.exists():
                test_data['images'][img_file] = img_path
                
        # Load checkcase data
        for item in orbit_path.iterdir():
            if item.is_dir() and item.name.startswith("Checkcase"):
                checkcase_data = self._load_checkcase_data(item)
                test_data['checkcases'][item.name] = checkcase_data
                
        return test_data
    
    def _load_checkcase_data(self, checkcase_path: Path) -> Dict:
        """Load data for an individual checkcase."""
        checkcase_data = {
            'path': checkcase_path,
            'summary_data': None,
            'images': {},
            'propagation_methods': []
        }
        
        # Load checkcase summary
        summary_file = checkcase_path / "summary.csv"
        if summary_file.exists():
            try:
                checkcase_data['summary_data'] = pd.read_csv(summary_file)
                # Clean column names (remove leading/trailing whitespace)
                if checkcase_data['summary_data'] is not None:
                    checkcase_data['summary_data'].columns = checkcase_data['summary_data'].columns.str.strip()
            except Exception as e:
                print(f"Warning: Could not load summary for {checkcase_path.name}: {e}")
                checkcase_data['summary_data'] = None
                
        # Load checkcase images
        for img_file in ["trajectory_comparison.png", "orbital_elements_comparison.png"]:
            img_path = checkcase_path / img_file
            if img_path.exists():
                checkcase_data['images'][img_file] = img_path
                
        # Discover propagation methods
        for item in checkcase_path.iterdir():
            if item.is_dir():
                checkcase_data['propagation_methods'].append(item.name)
                
        return checkcase_data
    
    def analyze_performance_metrics(self, summary_data: pd.DataFrame) -> Dict:
        """
        Analyze performance metrics from summary data.
        
        Args:
            summary_data: DataFrame containing test results
            
        Returns:
            Dictionary with analysis results
        """
        if summary_data is None or summary_data.empty:
            return {}
                
        analysis = {
            'propagation_methods': [],
            'checkcases': [],
            'position_error_stats': {},
            'velocity_error_stats': {},
            'best_performing_method': None,
            'worst_performing_method': None
        }
        
        # Check for required columns
        required_columns = ['Propagation', 'Checkcase', 'Mean Position Error', 'Mean Velocity Error']
        missing_columns = [col for col in required_columns if col not in summary_data.columns]
        
        if missing_columns:
            print(f"Warning: Missing required columns: {missing_columns}")
            return analysis
        
        try:
            analysis['propagation_methods'] = summary_data['Propagation'].unique().tolist()
            analysis['checkcases'] = summary_data['Checkcase'].unique().tolist()
            
            # Convert error strings to numeric values (remove units)
            def extract_numeric(series, unit_suffix):
                if series.dtype == 'object':
                    return pd.to_numeric(series.str.replace(unit_suffix, '').str.replace('e-', 'e-'), errors='coerce')
                return series
            
            # Extract numeric values for analysis
            mean_pos_error = extract_numeric(summary_data['Mean Position Error'], ' m')
            mean_vel_error = extract_numeric(summary_data['Mean Velocity Error'], ' cm/s')
            
            # Position error statistics
            if not mean_pos_error.isna().all():
                analysis['position_error_stats'] = {
                    'overall_mean': mean_pos_error.mean(),
                    'overall_std': mean_pos_error.std(),
                    'min': mean_pos_error.min(),
                    'max': mean_pos_error.max(),
                    'by_method': mean_pos_error.groupby(summary_data['Propagation']).agg(['mean', 'std']).to_dict()
                }
                
            # Velocity error statistics  
            if not mean_vel_error.isna().all():
                analysis['velocity_error_stats'] = {
                    'overall_mean': mean_vel_error.mean(),
                    'overall_std': mean_vel_error.std(),
                    'min': mean_vel_error.min(),
                    'max': mean_vel_error.max(),
                    'by_method': mean_vel_error.groupby(summary_data['Propagation']).agg(['mean', 'std']).to_dict()
                }
                
            # Find best and worst performing methods based on mean position error
            if not mean_pos_error.isna().all():
                method_performance = mean_pos_error.groupby(summary_data['Propagation']).mean().sort_values()
                if len(method_performance) > 0:
                    analysis['best_performing_method'] = method_performance.index[0]
                    analysis['worst_performing_method'] = method_performance.index[-1]
        
        except Exception as e:
            print(f"Warning: Error during performance analysis: {e}")
            
        return analysis
    
    def generate_orbit_section(self, orbit_data: Dict, manual_notes: str = "") -> str:
        """
        Generate a report section for a single orbit test.
        
        Args:
            orbit_data: Dictionary containing orbit test data
            manual_notes: Optional manual notes to include
            
        Returns:
            HTML string for the orbit section
        """
        html = f"""
        <div class="orbit-section">
            <h2>{orbit_data['orbit_name']}</h2>
            
            <div class="manual-notes">
                <h3>Test Notes</h3>
                <p>{manual_notes if manual_notes else 'No manual notes provided.'}</p>
            </div>
        """
        
        # Add summary analysis if available
        if orbit_data['summary_data'] is not None:
            analysis = self.analyze_performance_metrics(orbit_data['summary_data'])
            html += self._generate_analysis_html(analysis)
            html += self._generate_summary_table_html(orbit_data['summary_data'])
            
        # Add main comparison images
        html += self._generate_images_html(orbit_data['images'], "Main Comparisons")
        
        # Add checkcase details
        if orbit_data['checkcases']:
            html += "<h3>Checkcase Details</h3>"
            for checkcase_name, checkcase_data in orbit_data['checkcases'].items():
                html += self._generate_checkcase_html(checkcase_name, checkcase_data)
                
        html += "</div>"
        return html
    
    def _generate_analysis_html(self, analysis: Dict) -> str:
        """Generate HTML for performance analysis."""
        if not analysis:
            return ""
            
        html = """
        <div class="performance-analysis">
            <h3>Performance Analysis</h3>
            <div class="analysis-grid">
        """
        
        if analysis.get('best_performing_method'):
            html += f"""
            <div class="metric-box best">
                <h4>Best Performing Method</h4>
                <p>{analysis['best_performing_method']}</p>
            </div>
            """
            
        if analysis.get('worst_performing_method'):
            html += f"""
            <div class="metric-box worst">
                <h4>Worst Performing Method</h4>
                <p>{analysis['worst_performing_method']}</p>
            </div>
            """
            
        # Position error stats
        pos_stats = analysis.get('position_error_stats', {})
        if pos_stats:
            html += f"""
            <div class="metric-box">
                <h4>Position Error Statistics</h4>
                <p>Mean: {pos_stats.get('overall_mean', 'N/A'):.6f} m</p>
                <p>Std Dev: {pos_stats.get('overall_std', 'N/A'):.6f} m</p>
                <p>Range: {pos_stats.get('min', 'N/A'):.6e} - {pos_stats.get('max', 'N/A'):.6f} m</p>
            </div>
            """
            
        # Velocity error stats
        vel_stats = analysis.get('velocity_error_stats', {})
        if vel_stats:
            html += f"""
            <div class="metric-box">
                <h4>Velocity Error Statistics</h4>
                <p>Mean: {vel_stats.get('overall_mean', 'N/A'):.6f} cm/s</p>
                <p>Std Dev: {vel_stats.get('overall_std', 'N/A'):.6f} cm/s</p>
                <p>Range: {vel_stats.get('min', 'N/A'):.6e} - {vel_stats.get('max', 'N/A'):.6f} cm/s</p>
            </div>
            """
            
        html += """
            </div>
        </div>
        """
        return html
    
    def _generate_summary_table_html(self, summary_data: pd.DataFrame) -> str:
        """Generate HTML table from summary data."""
        if summary_data is None or summary_data.empty:
            return ""
            
        html = """
        <div class="summary-table">
            <h3>Detailed Results</h3>
            <div class="table-container">
        """
        
        # Convert DataFrame to HTML table with custom styling
        table_html = summary_data.to_html(
            classes=['results-table'], 
            table_id='summary-table',
            index=False,
            escape=False
        )
        
        html += table_html
        html += """
            </div>
        </div>
        """
        return html
        
    def _generate_images_html(self, images: Dict, section_title: str) -> str:
        """Generate HTML for displaying images."""
        if not images:
            return ""
            
        html = f"""
        <div class="images-section">
            <h3>{section_title}</h3>
            <div class="images-grid">
        """
        
        for img_name, img_path in images.items():
            if img_path.exists():
                # Convert image to base64 for embedding
                img_b64 = self._image_to_base64(img_path)
                html += f"""
                <div class="image-container">
                    <h4>{img_name.replace('_', ' ').replace('.png', '').title()}</h4>
                    <img src="data:image/png;base64,{img_b64}" alt="{img_name}">
                </div>
                """
                
        html += """
            </div>
        </div>
        """
        return html
    
    def _generate_checkcase_html(self, checkcase_name: str, checkcase_data: Dict) -> str:
        """Generate HTML for a checkcase section."""
        html = f"""
        <div class="checkcase-section">
            <h4>{checkcase_name}</h4>
            <div class="checkcase-content">
        """
        
        # Add propagation methods info
        if checkcase_data['propagation_methods']:
            methods_str = ", ".join(checkcase_data['propagation_methods'])
            html += f"<p><strong>Propagation Methods:</strong> {methods_str}</p>"
            
        # Add checkcase images if available
        if checkcase_data['images']:
            html += self._generate_images_html(checkcase_data['images'], f"{checkcase_name} Comparisons")
            
        html += """
            </div>
        </div>
        """
        return html
    
    def _image_to_base64(self, img_path: Path) -> str:
        """Convert image file to base64 string."""
        try:
            with open(img_path, "rb") as img_file:
                return base64.b64encode(img_file.read()).decode()
        except Exception as e:
            print(f"Warning: Could not encode image {img_path}: {e}")
            return ""
    
    def generate_full_report(self, output_path: str = None, manual_notes: Dict[str, str] = None) -> str:
        """
        Generate a complete HTML report for all orbit tests.
        
        Args:
            output_path: Path to save the report (optional)
            manual_notes: Dictionary mapping orbit names to manual notes
            
        Returns:
            HTML string of the complete report
        """
        if manual_notes is None:
            manual_notes = {}
            
        # Load all test results
        all_orbit_data = {}
        for orbit_name in self.orbit_tests:
            try:
                all_orbit_data[orbit_name] = self.load_test_results(orbit_name)
            except Exception as e:
                print(f"Warning: Could not load data for {orbit_name}: {e}")
                continue
                
        # Generate report HTML
        html = self._generate_html_header()
        
        # Add executive summary
        html += self._generate_executive_summary(all_orbit_data)
        
        # Add individual orbit sections
        for orbit_name, orbit_data in all_orbit_data.items():
            notes = manual_notes.get(orbit_name, "")
            html += self.generate_orbit_section(orbit_data, notes)
            
        html += self._generate_html_footer()
        
        # Save to file if requested
        if output_path:
            output_file = Path(output_path)
            output_file.parent.mkdir(parents=True, exist_ok=True)
            with open(output_file, 'w') as f:
                f.write(html)
            print(f"Report saved to: {output_file.absolute()}")
            
        return html
    
    def _generate_html_header(self) -> str:
        """Generate HTML header with styling."""
        return f"""
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>NASA 6DOF Orbital Test Results Report</title>
    <style>
        body {{
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            line-height: 1.6;
            color: #333;
            max-width: 1400px;
            margin: 0 auto;
            padding: 20px;
            background-color: #f5f5f5;
        }}
        
        .header {{
            text-align: center;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            color: white;
            padding: 30px;
            border-radius: 10px;
            margin-bottom: 30px;
            box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
        }}
        
        .orbit-section {{
            background: white;
            margin: 20px 0;
            padding: 30px;
            border-radius: 10px;
            box-shadow: 0 2px 10px rgba(0, 0, 0, 0.1);
        }}
        
        .performance-analysis {{
            background: #f8f9fa;
            padding: 20px;
            border-radius: 8px;
            margin: 20px 0;
            border-left: 5px solid #007bff;
        }}
        
        .analysis-grid {{
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(250px, 1fr));
            gap: 20px;
            margin-top: 15px;
        }}
        
        .metric-box {{
            background: white;
            padding: 15px;
            border-radius: 8px;
            border: 1px solid #dee2e6;
        }}
        
        .metric-box.best {{
            border-left: 5px solid #28a745;
        }}
        
        .metric-box.worst {{
            border-left: 5px solid #dc3545;
        }}
        
        .images-grid {{
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(400px, 1fr));
            gap: 20px;
            margin-top: 15px;
        }}
        
        .image-container {{
            text-align: center;
            background: white;
            padding: 15px;
            border-radius: 8px;
            box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
        }}
        
        .image-container img {{
            max-width: 100%;
            height: auto;
            border-radius: 4px;
        }}
        
        .table-container {{
            overflow-x: auto;
            margin-top: 15px;
        }}
        
        .results-table {{
            width: 100%;
            border-collapse: collapse;
            background: white;
        }}
        
        .results-table th, .results-table td {{
            padding: 12px;
            text-align: left;
            border-bottom: 1px solid #dee2e6;
        }}
        
        .results-table th {{
            background-color: #f8f9fa;
            font-weight: 600;
            position: sticky;
            top: 0;
        }}
        
        .results-table tr:hover {{
            background-color: #f5f5f5;
        }}
        
        .checkcase-section {{
            margin: 20px 0;
            padding: 15px;
            background: #f8f9fa;
            border-radius: 8px;
        }}
        
        .manual-notes {{
            background: #e3f2fd;
            padding: 15px;
            border-radius: 8px;
            border-left: 5px solid #2196f3;
            margin-bottom: 20px;
        }}
        
        h1, h2, h3, h4 {{
            color: #2c3e50;
        }}
        
        h2 {{
            border-bottom: 3px solid #3498db;
            padding-bottom: 10px;
        }}
        
        .summary-stats {{
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));
            gap: 15px;
            margin: 20px 0;
        }}
        
        .stat-card {{
            background: white;
            padding: 20px;
            border-radius: 8px;
            text-align: center;
            box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
        }}
        
        .stat-number {{
            font-size: 2em;
            font-weight: bold;
            color: #3498db;
        }}
    </style>
</head>
<body>
    <div class="header">
        <h1>NASA 6DOF Orbital Test Results Report</h1>
        <p>Generated on {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}</p>
    </div>
"""
    
    def _generate_executive_summary(self, all_orbit_data: Dict) -> str:
        """Generate an executive summary of all tests."""
        total_tests = len(all_orbit_data)
        total_checkcases = sum(len(data['checkcases']) for data in all_orbit_data.values())
        
        # Find all unique propagation methods
        all_methods = set()
        for orbit_data in all_orbit_data.values():
            if orbit_data['summary_data'] is not None:
                all_methods.update(orbit_data['summary_data']['Propagation'].unique())
        
        html = f"""
        <div class="orbit-section">
            <h2>Executive Summary</h2>
            
            <div class="summary-stats">
                <div class="stat-card">
                    <div class="stat-number">{total_tests}</div>
                    <div>Orbit Tests</div>
                </div>
                <div class="stat-card">
                    <div class="stat-number">{total_checkcases}</div>
                    <div>Total Checkcases</div>
                </div>
                <div class="stat-card">
                    <div class="stat-number">{len(all_methods)}</div>
                    <div>Propagation Methods</div>
                </div>
            </div>
            
            <h3>Tested Propagation Methods</h3>
            <ul>
        """
        
        for method in sorted(all_methods):
            html += f"<li>{method}</li>"
            
        html += """
            </ul>
            
            <h3>Available Orbit Tests</h3>
            <ul>
        """
        
        for orbit_name in sorted(all_orbit_data.keys()):
            checkcase_count = len(all_orbit_data[orbit_name]['checkcases'])
            html += f"<li><strong>{orbit_name}</strong> - {checkcase_count} checkcases</li>"
            
        html += """
            </ul>
        </div>
        """
        
        return html
    
    def _generate_html_footer(self) -> str:
        """Generate HTML footer."""
        return """
    <div class="orbit-section">
        <h2>Report Notes</h2>
        <p>This report was automatically generated from the NASA 6DOF orbital checkcase test results.</p>
        <p>All performance metrics are compared against reference solutions from NASA validation cases.</p>
        <p><strong>Position errors</strong> are reported in meters, <strong>velocity errors</strong> in cm/s.</p>
    </div>
</body>
</html>
"""

def main():
    """CLI interface for the report generator."""
    parser = argparse.ArgumentParser(description='Generate NASA 6DOF orbital test reports')
    parser.add_argument('--results-dir', type=str, help='Path to results directory')
    parser.add_argument('--output', '-o', type=str, default='nasa_6dof_report.html', 
                       help='Output HTML file path')
    parser.add_argument('--notes-file', type=str, help='Path to JSON file with manual notes')
    
    args = parser.parse_args()
    
    try:
        # Initialize report generator
        generator = NASA6DOFReportGenerator(args.results_dir)
        
        # Load manual notes if provided
        manual_notes = {}
        if args.notes_file and os.path.exists(args.notes_file):
            with open(args.notes_file, 'r') as f:
                manual_notes = json.load(f)
        else:
            default_notes_file = os.path.join(os.path.dirname(__file__), 'notes.json')
            with open(default_notes_file, 'r') as f:
                manual_notes = json.load(f)
        
        # Generate report
        print("Generating NASA 6DOF orbital test report...")
        html_report = generator.generate_full_report(args.output, manual_notes)
        
        print(f"✓ Report generated successfully!")
        print(f"✓ Found {len(generator.orbit_tests)} orbit test(s): {', '.join(generator.orbit_tests)}")
        
        # Open in browser if possible
        try:
            webbrowser.open(f"file://{Path(args.output).absolute()}")
            print(f"✓ Report opened in browser")
        except:
            print(f"✓ View report at: {Path(args.output).absolute()}")
            
    except Exception as e:
        print(f"Error: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()
