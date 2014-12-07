#!/bin/bash

# This script is to find a string from a list and manipulate the line in which the string appears
# Used to test the effect of removing single variables from the MVA training

# Known Issues
# - Skip the iteration if dummy01 is an empty variable
# - A way to add lines

# Base set used: test299
# Warning: Make sure the input file matches exactly the base set

# File whose contents to be manipulated
MainDir="/afs/cern.ch/work/a/afiqaize/thq/PECLocalFwk/Part3_OpMVA/Classification/Train/"
InDir="/afs/cern.ch/work/a/afiqaize/thq/PECLocalFwk/Part3_OpMVA/Classification/Mytrain/"
InFile=$InDir"trainMVA.cpp"

# List of variables
VarsList01="glb_Charge_Lep
glb_Sphericity
thq_NumBTag_Higgs"

VarsList02="thq_Pt_Higgs
thq_Pt_Recoil
thq_Rap_Recoil"

VarsList03="tt_DeltaR_Light
tt_Mass_WHad
tt_NumPassBTag_Light"

# Set up miscellaneous variables and go to the right directory
slash="/"
slashes="//"
latestTest=348
outDir01="/afs/cern.ch/work/a/afiqaize/thq/PECLocalFwk/Part3_OpMVA/Classification/newSets/test"
log="log"
txt=".txt"
test="test"
message01=" was removed from the test342 set."
extension=".root"

source /afs/cern.ch/work/a/afiqaize/PEC_env.sh
cd $InDir

# Start the loop to remove each variable and do the test
for vars in $VarsList03
do

# Prepare the directory and logfiles and other random stuff
((latestTest++))
outDir02=$outDir01$latestTest
mkdir $outDir02

outLog=$outDir02$slash$log$latestTest$txt
testName=$test$latestTest
message02=$vars$message01
fileName=$testName$extension

echo $outLog > $outLog
echo $message02 >> $outLog
echo "" >> $outLog

# Remove the variable out of the list
dummy01=$(grep $vars $InFile)
dummy02=$slashes$dummy01
sed -i "s#$dummy01#$dummy02#g" $InFile

# Start the training
make
./trainMVA >> $outLog
python discrPlots.py infoTHvsTTbar_Global.root THvsTTbar_Global_BFGS $testName
mv infoTHvsTTbar_Global.root $fileName
mv $fileName $MainDir
cp -r fig $outDir02
cp -r weights $outDir02

# Restore the file back to its original state
sed -i "s#$dummy02#$dummy01#g" $InFile;

done