#!/bin/bash

set -euo pipefail

if [[ -z "${PR_TITLE:-}" ]]; then
    echo "PR title validation failed: PR_TITLE is not set."
    exit 1
fi

echo "Validating PR title: $PR_TITLE"

# Required format:
#   [MARKER] short description (#123)
# or
#   [MARKER] short description #123
# Allowed markers come from scripts/increment_version.sh.
marker_regex='^\[(MAJOR|BREAKING|MINOR|FEATURE|IMPROVEMENT|PATCH|BUGFIX|FIX|HOTFIX|CHORE|DOCS|REFACTOR|PERF|TEST|CI)\]'
issue_suffix_regex='(\(#[0-9]+\)|#[0-9]+)$'
title_regex='^\[(MAJOR|BREAKING|MINOR|FEATURE|IMPROVEMENT|PATCH|BUGFIX|FIX|HOTFIX|CHORE|DOCS|REFACTOR|PERF|TEST|CI)\].*(\(#[0-9]+\)|#[0-9]+)$'

# Keep strict title validation for everyone, but normalize Dependabot PRs by
# appending a synthetic issue marker when one is not present.
if [[ "${PR_AUTHOR:-}" == "dependabot[bot]" ]]; then
    if printf '%s\n' "$PR_TITLE" | grep -Eiq "$marker_regex" && ! printf '%s\n' "$PR_TITLE" | grep -Eiq "$issue_suffix_regex"; then
        if [[ -z "${PR_NUMBER:-}" || -z "${REPO:-}" || -z "${API_URL:-}" || -z "${GITHUB_TOKEN:-}" ]]; then
            echo "PR title validation failed: missing API env vars needed to update Dependabot PR title."
            exit 1
        fi

        new_title="$PR_TITLE (#0)"
        echo "Dependabot PR is missing issue suffix; updating title to: $new_title"
        payload="$(jq -nc --arg title "$new_title" '{title: $title}')"
        curl -fsSL -X PATCH \
            -H "Authorization: Bearer $GITHUB_TOKEN" \
            -H "Accept: application/vnd.github+json" \
            -H "Content-Type: application/json" \
            "$API_URL/repos/$REPO/pulls/$PR_NUMBER" \
            -d "$payload" >/dev/null
        PR_TITLE="$new_title"
    fi
fi

if ! printf '%s\n' "$PR_TITLE" | grep -Eiq "$title_regex"; then
    echo "PR title validation failed."
    echo "Expected format: [MARKER] description (#123)"
    echo "Also accepted: [MARKER] description #123"
    echo "Use (#0) when there is no associated issue."
    echo "Allowed markers: [MAJOR], [BREAKING], [MINOR], [FEATURE], [IMPROVEMENT], [PATCH], [BUGFIX], [FIX], [HOTFIX], [CHORE], [DOCS], [REFACTOR], [PERF], [TEST], [CI]"
    exit 1
fi

echo "PR title is valid."