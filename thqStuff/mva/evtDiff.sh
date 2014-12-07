#!/bin/bash

# This script is to take the input of two text files, sort them up numerically and record their differences.
# To check the issue with different event yields in ttbar-semilep after runs

# Known issues:
# - naming scheme
# - maybe some way so that we don't need to use splitTuples first?

# Directory definitions as usual
inDir="/home/ieeya/Downloads/tHq/Part3_OpMVA/Classification/newFiles/tuples_"
outDir="/home/ieeya/Downloads/tHq/Part3_OpMVA/Classification/newFiles/docs/"

# The run to be compared (where the text files exist) (it is necessary that an identifier exists)
# Only this part should be manipulated
runFirst="deBug01"
runSecond="deBug02"

# Miscellaneous variables
txt=".txt"
udsc="_"
slash="/"

# List of files to be looped over
fileList="thq-nc-mg_train
thq-nc-mg_exam
ttbar-dilep-mg_train
ttbar-dilep-mg_exam
ttbar-semilep-mg_train
ttbar-semilep-mg_exam
tth_train
tth_exam
t-tchan-pw_train
t-tchan-pw_exam
t-tWchan-pw_train
t-tWchan-pw_exam
Wjets-mg_train
Wjets-mg_exam"

#fileTT="ttbar-semilep-mg_train
#ttbar-semilep-mg_exam"

fileTT="ttbar-semilep-mg-p1_53X.02.01_VNz_p1_ele
ttbar-semilep-mg-p1_53X.02.01_VNz_p1_mu
ttbar-semilep-mg-p1_53X.02.01_VNz_p2_ele
ttbar-semilep-mg-p1_53X.02.01_VNz_p2_mu
ttbar-semilep-mg-p1_53X.02.01_VNz_p3_ele
ttbar-semilep-mg-p1_53X.02.01_VNz_p3_mu
ttbar-semilep-mg-p1_53X.02.01_VNz_p4_ele
ttbar-semilep-mg-p1_53X.02.01_VNz_p4_mu"

# Dummy files initialization
outDum01=$outDir"dum01"$txt
outDum02=$outDir"dum02"$txt

for file in $fileTT
do

# Link up the right files
inFirst=$inDir$runFirst$slash$file$txt
inSecond=$inDir$runSecond$slash$file$txt

outFile=$outDir$file$udsc$runFirst$udsc$runSecond$txt

# Sort them numerically
sort -n $inFirst > $outDum01
sort -n $inSecond > $outDum02

# Find the differences in the files
diff -d $outDum01 $outDum02 > $outFile

# Delete the dummies
rm $outDum01
rm $outDum02

done