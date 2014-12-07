#!/bin/bash

# This script is to find a string from a list and manipulate the line in which the string appears
# Used to train the MVA against a single background process
# based on the results of test62

# Known Issues
# - Does it even run properly? Let's see...

# File whose contents to be manipulated
InFile="/afs/cern.ch/work/a/afiqaize/thq/PECLocalFwk/Part3_OpMVA/Classification/Selftrain/trainMVA.cpp"

# List of background processes
ProList="tth
t-tchan
t-schan
t-tWchan
Wjets"

# Set up miscellaneous variables and go to the right directory
slash="/"
semicol=";"
latestTest=64
outDir01="/afs/cern.ch/work/a/afiqaize/thq/PECLocalFwk/Part3_OpMVA/Classification/newSets/test"
log="log"
txt=".txt"
test="test"
message01=" was the background considered in this training."
bkgSet="int bkgUsed = "
bkgNo=2

source /afs/cern.ch/work/a/afiqaize/PEC_env.sh
cd Part3_OpMVA/Classification/Selftrain/

# Start the loop to remove each variable and do the test
for pro in $ProList
do

# Prepare the directory and logfiles and other random stuff
((latestTest++))
outDir02=$outDir01$latestTest
mkdir $outDir02

outLog=$outDir02$slash$log$latestTest$txt
testName=$test$latestTest
message02=$pro$message01

echo $outLog > $outLog
echo $message02 >> $outLog
echo "" >> $outLog

# Change the variable bkgUsed in the trainMVA (amounts to using only one process as background)
((bkgNo++))
dummy01=$(grep "int bkgUsed" $InFile)
dummy02=$bkgSet$bkgNo$semicol
sed -i "s#$dummy01#$dummy02#g" $InFile

# Start the training
make
./trainMVA >> $outLog
python discrPlots.py infoTHvsTTbar_Global.root THvsTTbar_Global_BFGS $testName >> $outLog
cp -r fig $outDir02
cp infoTHvsTTbar_Global.root $outDir02

# Restore the file back to its original state
sed -i "s#$dummy02#$dummy01#g" $InFile;

done 
