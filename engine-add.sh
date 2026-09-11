#!/bin/bash
if ! git ls-remote --exit-code --heads "engine-upstream" main > /dev/null 2>&1; then
    git remote add engine-upstream  https://github.com/Eisen-W/BMengine.git
    if [ -d "engine/" ]; then
        rm -rf "engine/"
    fi
fi

git add .
git commit -m "before adding engine subtree"
if [ ! -d "engine/" ]; then
    git subtree add --prefix=engine/ engine-upstream main --squash
fi
cd engine || exit
echo "cd to engine"
shopt -s extglob
rm -rf !(engine)
rm -f .clang-tidy
rm -f .gitattributes
rm -f .gitignore
echo "removed all except engine subfolder"
mv engine/* .
mv engine empty
if [ -z "$(ls -A empty)" ]; then
    rm -r empty
fi
echo "removed empty engine folder"
cd ..
echo "cd back to parent dir"
git add .
git commit -m "added engine remote"