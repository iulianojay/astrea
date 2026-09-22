#!/bin/sh

#get highest tag number
VERSION=`git describe --abbrev=0 --tags`

#get number parts and increase last one by 1
VNUM1=$(echo "$VERSION" | cut -d"." -f1)
VNUM2=$(echo "$VERSION" | cut -d"." -f2)
VNUM3=$(echo "$VERSION" | cut -d"." -f3)
VNUM1=`echo $VNUM1 | sed 's/v//'`

# Check commit message markers and increment the relevant version number.
# Supported markers (case-insensitive):
#   Major: [MAJOR], [BREAKING]
#   Minor: [MINOR], [FEATURE], [IMPROVEMENT]
#   Patch: [PATCH], [BUGFIX], [FIX], [HOTFIX], [CHORE], [DOCS], [REFACTOR], [PERF], [TEST], [CI]
COMMIT_MSG="$(git log --format=%B -n 1 HEAD)"
MAJOR=$(printf '%s\n' "$COMMIT_MSG" | grep -Eiq '\[(major|breaking)\]' && echo 1 || true)
MINOR=$(printf '%s\n' "$COMMIT_MSG" | grep -Eiq '\[(minor|feature|improvement)\]' && echo 1 || true)

if [ "$MAJOR" ]; then
    echo "Update major version"
    VNUM1=$((VNUM1+1))
    VNUM2=0
    VNUM3=0
elif [ "$MINOR" ]; then
    echo "Update minor version"
    VNUM2=$((VNUM2+1))
    VNUM3=0
else
    echo "Update patch version"
    VNUM3=$((VNUM3+1))
fi

#create new tag
NEW_TAG="$VNUM1.$VNUM2.$VNUM3"

echo "Updating $VERSION to $NEW_TAG"

#get current hash and see if it already has a tag
GIT_COMMIT=`git rev-parse HEAD`
NEEDS_TAG=`git describe --contains $GIT_COMMIT 2>/dev/null`

#only tag if no tag already (would be better if the git describe command above could have a silent option)
if [ -z "$NEEDS_TAG" ]; then
    echo "Tagged with $NEW_TAG (Ignoring fatal:cannot describe - this means commit is untagged) "
    git tag $NEW_TAG
    git push --tags
else
    echo "Already a tag on this commit"
fi