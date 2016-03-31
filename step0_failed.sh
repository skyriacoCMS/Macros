#!/bin/bash


echo ""
echo "CMSSW on Condor"
echo ""

#START_TIME=`/bin/date`
#echo "started at $START_TIME"

source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc6_amd64_gcc481

cd /uscms_data/d3/skyria/Stealth_13/March16/CMSSW_7_6_3/src/SIG_gen/1000_200/
eval `scramv1 runtime -sh`

cd ${_CONDOR_SCRATCH_DIR}


FILE=EMPTY.txt
k=0
INPUT="input "
OUTPUT="file:./"
OUTPUTLOCAL=""
EOSOUT="root://cmseos.fnal.gov//store/user/skyria/Stealth_13/March15/SIG/100\
0_200/GENSIM/"
EVNUM=""
while read line;do
   # echo $line
   # echo "k bf: $k"
    if [ "$k" = "$1"  ]; then
	end1="01"
	end2="GENSIM_RAWv12.root"
	end3="_GENSIM_RAWv12.root"
	echo "in if now "
	INPUT="$INPUT $line"
	EVNUM=$line$end1
	OUTPUT=$OUTPUT$line$end2
	OUTPUTLOCAL=$line$end2
	EOSOUT=$EOSOUT$line$end3
    fi
    ((k++))


done < $FILE

echo $INPUT

echo $INPUT
echo $EVNUM
echo $OUTPUT
echo $OUTPUTLOCAL
echo $EOSOUT


cmsRun /uscms_data/d3/skyria/Stealth_13/March16/CMSSW_7_6_3/src/SIG_gen/1000_200/step0_LHE_GEN_SIM_v76.py $EVNUM $OUTPUT 
xrdcp $OUTPUTLOCAL $EOSOUT
rm $OUTPUTLOCAL



