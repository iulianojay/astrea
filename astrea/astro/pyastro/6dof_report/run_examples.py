#!/usr/bin/env python3
"""
Example usage script for NASA 6DOF Report Generator

This demonstrates various ways to use the report generator class.

An AI wrote this file.
"""

import sys
from pathlib import Path

# Add the current directory to the Python path
sys.path.insert(0, str(Path(__file__).parent))

from nasa_6dof_report import NASA6DOFReportGenerator

def example_basic_usage():
    """Basic usage example - generate report with default settings."""
    print("=== Basic Usage Example ===")
    
    # Initialize the generator (auto-discovers results directory)
    generator = NASA6DOFReportGenerator()
    
    # Generate a basic report
    html_report = generator.generate_full_report("basic_report.html")
    print("✓ Basic report generated as 'basic_report.html'")
    

def example_with_manual_notes():
    """Example with manual annotations."""
    print("\n=== Usage with Manual Notes ===")
    
    generator = NASA6DOFReportGenerator()
    
    # Define manual notes for each orbit test
    manual_notes = {
        "Orbit_02": "Baseline two-body dynamics validation. All methods should show excellent agreement.",
        "Orbit_03A": "Atmospheric drag test - continuous acceleration challenges for numerical methods.",
        "Orbit_03B": "Alternative atmospheric model validation.",
        "Orbit_04": "High-eccentricity orbit - tests numerical stability at periapsis."
    }
    
    # Generate report with notes
    html_report = generator.generate_full_report("annotated_report.html", manual_notes)
    print("✓ Annotated report generated as 'annotated_report.html'")


def example_single_orbit_analysis():
    """Example analyzing a single orbit test in detail."""
    print("\n=== Single Orbit Analysis ===")
    
    generator = NASA6DOFReportGenerator()
    
    # Load data for a specific orbit
    orbit_data = generator.load_test_results("Orbit_02")
    
    # Analyze performance metrics
    if orbit_data['summary_data'] is not None:
        analysis = generator.analyze_performance_metrics(orbit_data['summary_data'])
        
        print(f"Best performing method: {analysis.get('best_performing_method', 'N/A')}")
        print(f"Worst performing method: {analysis.get('worst_performing_method', 'N/A')}")
        
        pos_stats = analysis.get('position_error_stats', {})
        if pos_stats:
            print(f"Overall mean position error: {pos_stats.get('overall_mean', 'N/A'):.6f} m")
            
    print("✓ Single orbit analysis completed")


def example_custom_results_directory():
    """Example using a custom results directory."""
    print("\n=== Custom Results Directory ===")
    
    # Specify a custom results directory
    custom_dir = "/home/jay/projects/astrea/astrea/astro/tests/nasa_6dof_checkcases/orbital/results"
    
    try:
        generator = NASA6DOFReportGenerator(custom_dir)
        
        print(f"Found orbit tests: {generator.orbit_tests}")
        
        # Generate report
        html_report = generator.generate_full_report("custom_dir_report.html")
        print("✓ Custom directory report generated as 'custom_dir_report.html'")
        
    except FileNotFoundError as e:
        print(f"⚠ Custom directory not found: {e}")


if __name__ == "__main__":
    print("NASA 6DOF Report Generator - Usage Examples")
    print("=" * 50)
    
    # Run all examples
    try:
        example_basic_usage()
        example_with_manual_notes()
        example_single_orbit_analysis()
        example_custom_results_directory()
        
        print("\n" + "=" * 50)
        print("✓ All examples completed successfully!")
        print("\nTo run the full CLI interface:")
        print("python nasa_6dof_report.py --output my_report.html --notes-file example_notes.json")
        
    except Exception as e:
        print(f"\n❌ Error running examples: {e}")
        print("Make sure the test results directory exists and contains valid data.")