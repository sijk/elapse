#!/bin/bash

#
# Copy the template test and rename it appropriately
#

if [[ $# != 1 ]]
then
    echo "usage: $0 TestName"
    exit 1
fi

testname="$1"

if $(grep -vq '^[[:upper:]]' <(echo "$testname"))
then
    echo "Error: The test name should be in CamelCase."
    exit 1
fi

testlower=$(echo "$testname" | sed 's/.*/\L&/')
cd $(dirname $0)

if [[ -d "$testlower" ]]
then
    echo "Error: A directory called $testlower already exists."
    exit 1
fi

cp -r template "$testlower"
cd "$testlower"

for f in CMakeLists.txt template_test.cpp
do
    sed -i "s/template/$testlower/g" "$f"
    sed -i "s/Template/$testname/g" "$f"
done

mv "template_test.cpp" "${testlower}_test.cpp"

cd ..

echo "add_subdirectory($testlower)" >> CMakeLists.txt
