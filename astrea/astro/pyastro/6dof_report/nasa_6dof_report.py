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
import argparse
import json
import shutil

try:
    import matplotlib.pyplot as plt
    import matplotlib.image as mpimg
    MATPLOTLIB_AVAILABLE = True
except ImportError:
    MATPLOTLIB_AVAILABLE = False
    print("Warning: matplotlib not available. Some plotting features may be limited.")

# This is so stupid
OUTPUT_BASE = Path(__file__).parent.parent.parent.parent.parent / "docs" / "design" / "nasa_6dof_report"

class NASA6DOFReportGenerator:
    """Class for generating comprehensive reports from NASA 6DOF orbital test results."""
    
    def __init__(self, custom_introduction: str = None):
        """
        Initialize the report generator.
        
        Args:
            results_dir: Path to the orbital results directory
            custom_introduction: Custom introduction text for the report
        """
        # Default to the standard location
        actual_results_dir = Path(__file__).parent.parent.parent / "tests" / "nasa_6dof_checkcases" / "orbital" / "results"

        self.results_dir = Path(OUTPUT_BASE / "results")
        os.makedirs(self.results_dir, exist_ok=True)
        shutil.copytree(actual_results_dir, self.results_dir, dirs_exist_ok=True)
        
        self.custom_introduction = custom_introduction
            
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
            summary_data: DataFrame with test results
            
        Returns:
            Dictionary with analysis results
        """
        if summary_data is None or summary_data.empty:
            return {}
            
        analysis = {}
        
        try:
            # Position RMS error analysis
            if 'Position RMS Error (m)' in summary_data.columns:
                pos_errors = summary_data['Position RMS Error (m)']
                best_pos_idx = pos_errors.idxmin()
                worst_pos_idx = pos_errors.idxmax()
                
                analysis['best_position_rms'] = {
                    'value': pos_errors[best_pos_idx],
                    'propagation': summary_data.loc[best_pos_idx, 'Propagation']
                }
                analysis['worst_position_rms'] = {
                    'value': pos_errors[worst_pos_idx],
                    'propagation': summary_data.loc[worst_pos_idx, 'Propagation']
                }
                
            # Velocity RMS error analysis
            if 'Velocity RMS Error (m/s)' in summary_data.columns:
                vel_errors = summary_data['Velocity RMS Error (m/s)']
                best_vel_idx = vel_errors.idxmin()
                worst_vel_idx = vel_errors.idxmax()
                
                analysis['best_velocity_rms'] = {
                    'value': vel_errors[best_vel_idx],
                    'propagation': summary_data.loc[best_vel_idx, 'Propagation']
                }
                analysis['worst_velocity_rms'] = {
                    'value': vel_errors[worst_vel_idx],
                    'propagation': summary_data.loc[worst_vel_idx, 'Propagation']
                }
                
        except Exception as e:
            print(f"Warning: Error analyzing performance metrics: {e}")
            
        return analysis
    
    def _generate_markdown_header(self) -> str:
        """Generate Markdown header with frontmatter."""
        current_time = datetime.now().strftime("%B %d, %Y at %H:%M:%S")
        return f'''---
title: "Comparison to NASA 6DoF Checkcases"
description: "Validation report comparing ASTREA orbital propagation results against NASA 6DoF reference checkcases"
---

# Comparison to NASA 6DoF Checkcases

This report presents a comprehensive comparison of ASTREA's orbital propagation capabilities against NASA's 6 Degree of Freedom (6DoF) reference checkcases. The validation demonstrates ASTREA's accuracy and reliability for astrodynamics computations by comparing trajectory propagation results across multiple orbital scenarios and numerical integration methods.

*Report generated on {current_time}*

'''

    def generate_orbit_section_markdown(self, orbit_data: Dict, manual_notes: str = "") -> str:
        """
        Generate a report section for a single orbit test in Markdown format.
        
        Args:
            orbit_data: Dictionary containing orbit test data
            manual_notes: Optional manual notes to include
            
        Returns:
            Markdown string for the orbit section
        """
        markdown = f"\n## {orbit_data['orbit_name']}\n\n"
        
        # Add test notes
        if manual_notes:
            markdown += "### Test Notes\n\n"
            markdown += f"{manual_notes}\n\n"
        
        # Add summary analysis if available
        if orbit_data['summary_data'] is not None:
            analysis = self.analyze_performance_metrics(orbit_data['summary_data'])
            markdown += self._generate_analysis_markdown(analysis)
            markdown += self._generate_summary_table_markdown(orbit_data['summary_data'])
            
        # Add main comparison images
        markdown += self._generate_images_markdown(orbit_data['images'], "Main Comparisons")
        
        # Add checkcase details
        if orbit_data['checkcases']:
            markdown += "### Checkcase Details\n\n"
            for checkcase_name, checkcase_data in orbit_data['checkcases'].items():
                markdown += self._generate_checkcase_markdown(checkcase_name, checkcase_data)
                
        return markdown

    def _generate_analysis_markdown(self, analysis: Dict) -> str:
        """Generate Markdown for performance analysis."""
        if not analysis:
            return ""
            
        markdown = "### Performance Analysis\n\n"
        
        # Position error analysis
        if 'best_position_rms' in analysis:
            best_pos = analysis['best_position_rms']
            worst_pos = analysis['worst_position_rms']
            
            markdown += "!!! success \"Position Accuracy\"\n"
            markdown += f"    **Best RMS Position Error**: {best_pos['value']:.3e} km ({best_pos['propagation']})\n\n"
            
            markdown += "!!! warning \"Position Accuracy\"\n"
            markdown += f"    **Worst RMS Position Error**: {worst_pos['value']:.3e} km ({worst_pos['propagation']})\n\n"
        
        # Velocity error analysis
        if 'best_velocity_rms' in analysis:
            best_vel = analysis['best_velocity_rms']
            worst_vel = analysis['worst_velocity_rms']
            
            markdown += "!!! success \"Velocity Accuracy\"\n"
            markdown += f"    **Best RMS Velocity Error**: {best_vel['value']:.3e} km/s ({best_vel['propagation']})\n\n"
            
            markdown += "!!! warning \"Velocity Accuracy\"\n"
            markdown += f"    **Worst RMS Velocity Error**: {worst_vel['value']:.3e} km/s ({worst_vel['propagation']})\n\n"
        
        return markdown

    def _generate_summary_table_markdown(self, summary_data: pd.DataFrame) -> str:
        """Generate Markdown table from summary data."""
        if summary_data is None or summary_data.empty:
            return ""
            
        markdown = "### Detailed Results\n\n"
        
        # Convert DataFrame to markdown table
        markdown += summary_data.to_markdown(index=False, tablefmt="pipe")
        markdown += "\n\n"
        
        return markdown

    def _generate_images_markdown(self, images: Dict, section_title: str) -> str:
        """Generate Markdown for displaying images."""
        if not images:
            return ""
            
        markdown = f"### {section_title}\n\n"
        
        for img_name, img_path in images.items():
            if img_path.exists():
                # Convert path to relative path from docs directory 
                rel_path = os.path.relpath(img_path, start=Path("../../../../docs/design/nasa_6dof_report").resolve())
                img_title = img_name.replace('_', ' ').replace('.png', '').title()
                
                markdown += f"#### {img_title}\n\n"
                markdown += f"![{img_title}]({rel_path})\n\n"
                
        return markdown

    def _generate_checkcase_markdown(self, checkcase_name: str, checkcase_data: Dict) -> str:
        """Generate Markdown for a checkcase section."""
        markdown = f"#### {checkcase_name}\n\n"
        
        # Add propagation methods info
        if checkcase_data['propagation_methods']:
            methods_str = ", ".join(checkcase_data['propagation_methods'])
            markdown += f"**Propagation Methods:** {methods_str}\n\n"
            
        # Add checkcase images if available
        if checkcase_data['images']:
            markdown += self._generate_images_markdown(checkcase_data['images'], f"{checkcase_name} Comparisons")
            
        return markdown

    def generate_full_report(self, output_path: str = None, manual_notes: Dict[str, str] = None) -> str:
        """
        Generate a complete Markdown report for all orbit tests.
        
        Args:
            output_path: Path to save the report (optional)
            manual_notes: Dictionary mapping orbit names to manual notes
            
        Returns:
            Markdown string of the complete report
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
                
        # Generate report Markdown
        markdown = self._generate_markdown_header()
        
        # Add custom introduction if provided
        if self.custom_introduction:
            markdown += f"\n{self.custom_introduction}\n\n"
        
        # Add executive summary
        markdown += self._generate_executive_summary_markdown(all_orbit_data)
        
        # Add individual orbit sections
        for orbit_name, orbit_data in all_orbit_data.items():
            notes = manual_notes.get(orbit_name, "")
            markdown += self.generate_orbit_section_markdown(orbit_data, notes)
            
        # Save to file if requested
        if output_path:
            output_file = Path(output_path)
            output_file.parent.mkdir(parents=True, exist_ok=True)
            with open(output_file, 'w') as f:
                f.write(markdown)
            print(f"Report saved to: {output_file.absolute()}")
            
        return markdown

    def _generate_executive_summary_markdown(self, all_orbit_data: Dict) -> str:
        """Generate an executive summary of all tests in Markdown format."""
        total_tests = len(all_orbit_data)
        total_checkcases = sum(len(data['checkcases']) for data in all_orbit_data.values())
        
        # Find all unique propagation methods
        all_methods = set()
        for orbit_data in all_orbit_data.values():
            if orbit_data['summary_data'] is not None:
                all_methods.update(orbit_data['summary_data']['Propagation'].unique())
        
        markdown = f'''## Executive Summary

This validation study encompasses **{total_tests} orbital test cases** with **{total_checkcases} total checkcases**, evaluating **{len(all_methods)} distinct propagation methods**. The tests validate ASTREA's orbital mechanics implementation against established NASA reference solutions.

!!! info "Test Coverage"
    - **{total_tests}** Orbit Tests
    - **{total_checkcases}** Total Checkcases  
    - **{len(all_methods)}** Propagation Methods

### Tested Propagation Methods

The following numerical integration methods were evaluated:

'''
        
        for method in sorted(all_methods):
            markdown += f"- **{method}**\n"
            
        markdown += "\n### Available Orbit Tests\n\n"
        
        for orbit_name in sorted(all_orbit_data.keys()):
            checkcase_count = len(all_orbit_data[orbit_name]['checkcases'])
            markdown += f"- **{orbit_name}** - {checkcase_count} checkcases\n"
            
        markdown += "\n"
        return markdown


def main():
    """CLI interface for the report generator."""
    parser = argparse.ArgumentParser(description='Generate NASA 6DOF orbital test reports in Markdown format')
    parser.add_argument('--notes-file', type=str, help='Path to JSON file with manual notes')
    parser.add_argument('--introduction', type=str, help='Custom introduction text for the report')
    
    args = parser.parse_args()
    
    try:
        # Initialize report generator
        generator = NASA6DOFReportGenerator(args.introduction)
        
        # Load manual notes if provided
        manual_notes = {}
        if args.notes_file and os.path.exists(args.notes_file):
            with open(args.notes_file, 'r') as f:
                manual_notes = json.load(f)
        else:
            default_notes_file = os.path.join(os.path.dirname(__file__), 'notes.json')
            if os.path.exists(default_notes_file):
                with open(default_notes_file, 'r') as f:
                    manual_notes = json.load(f)

        output_path = Path(OUTPUT_BASE / 'nasa_6dof_report.md')
        
        # Generate report
        print("Generating NASA 6DOF orbital test report...")
        markdown_report = generator.generate_full_report(output_path, manual_notes)
        
        print(f"✓ Report generated successfully!")
        print(f"✓ Found {len(generator.orbit_tests)} orbit test(s): {', '.join(generator.orbit_tests)}")
        print(f"✓ Markdown report saved to: {output_path.absolute()}")
            
    except Exception as e:
        print(f"Error: {e}")
        sys.exit(1)
        

if __name__ == "__main__":
    main()