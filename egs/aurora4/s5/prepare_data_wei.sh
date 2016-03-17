#!/bin/bash

# author:wei

if [ $# -ne 1 ]; then
    printf "\nUSAGE: %s <corpus-directory>\n\n" `basename $0`
    echo "The argument should be a the top-level WSJ corpus directory."
    echo "It is assumed that there will be a 'wsj0' and a 'wsj1' subdirectory"
    echo "within the top-level corpus directory."
    exit 1;
fi

AURORA=$1

dir=`pwd`/data/local/data/test_4sets
mkdir -p $dir
local=`pwd`/local
utils=`pwd`/utils

. ./path.sh # Needed for KALDI_ROOT
export PATH=$PATH:$KALDI_ROOT/tools/irstlm/bin
sph2pipe=$KALDI_ROOT/tools/sph2pipe_v2.5/sph2pipe
if [ ! -x $sph2pipe ]; then
echo "Could not find (or execute) the sph2pipe program at $sph2pipe";
exit 1;
fi

cd $dir


#Test Set
for x in 01; do
    cat $AURORA/lists/test${x}_0330_16k.list \
    | $local/aurora2flist.pl $AURORA | sort -u > test_A_${x}.flist || exit 1
done

for x in $(seq -f "%02g" 02 07); do
    cat $AURORA/lists/test${x}_0330_16k.list \
    | $local/aurora2flist.pl $AURORA | sort -u > test_B_${x}.flist || exit 1
done

for x in 08; do
    cat $AURORA/lists/test${x}_0330_16k.list \
    | $local/aurora2flist.pl $AURORA | sort -u > test_C_${x}.flist || exit 1
done

for x in $(seq -f "%02g" 09 14); do
    cat $AURORA/lists/test${x}_0330_16k.list \
    | $local/aurora2flist.pl $AURORA | sort -u > test_D_${x}.flist || exit 1
done


# Trans and sph for Test Set
for x in 01; do

    $local/flist2scp_12.pl test_A_${x}.flist | sort > test_A_${x}_sph_tmp.scp || exit 1

    cat test_A_${x}_sph_tmp.scp | awk '{print $1}' \
        | $local/find_transcripts.pl dot_files.flist > test_A_${x}_tmp.trans1
    cat test_A_${x}_sph_tmp.scp | perl -e \
    ' $condition="$ARGV[0]";
        if ($condition eq "01") {$suffix=0;}
        elsif ($condition eq "02") {$suffix=1;} 
        elsif ($condition eq "03") {$suffix=2;} 
        elsif ($condition eq "04") {$suffix=3;} 
        elsif ($condition eq "05") {$suffix=4;} 
        elsif ($condition eq "06") {$suffix=5;} 
        elsif ($condition eq "07") {$suffix=6;} 
        elsif ($condition eq "08") {$suffix=7;} 
        elsif ($condition eq "09") {$suffix=8;} 
        elsif ($condition eq "10") {$suffix=9;} 
        elsif ($condition eq "11") {$suffix=a;} 
        elsif ($condition eq "12") {$suffix=b;} 
        elsif ($condition eq "13") {$suffix=c;} 
        elsif ($condition eq "14") {$suffix=d;} 
        else {print STDERR "error condition $condition";}
        while(<STDIN>)
        {
            @A=split(" ", $_);  
            print $A[0].$suffix." ".$A[1]."\n";
        }
    ' $x > test_A_${x}_sph.scp || exit 1


    cat test_A_${x}_tmp.trans1 | perl -e \
    ' $condition="$ARGV[0]";
        if ($condition eq "01") {$suffix=0;}
        elsif ($condition eq "02") {$suffix=1;} 
        elsif ($condition eq "03") {$suffix=2;} 
        elsif ($condition eq "04") {$suffix=3;} 
        elsif ($condition eq "05") {$suffix=4;} 
        elsif ($condition eq "06") {$suffix=5;} 
        elsif ($condition eq "07") {$suffix=6;} 
        elsif ($condition eq "08") {$suffix=7;} 
        elsif ($condition eq "09") {$suffix=8;} 
        elsif ($condition eq "10") {$suffix=9;} 
        elsif ($condition eq "11") {$suffix=a;} 
        elsif ($condition eq "12") {$suffix=b;} 
        elsif ($condition eq "13") {$suffix=c;} 
        elsif ($condition eq "14") {$suffix=d;} 
        else {print STDERR "error condition $condition";}
        while(<STDIN>)
        {
            @A=split(" ", $_);  
            print $A[0].$suffix;
            for ($i=1; $i < @A; $i++) {print " ".$A[$i];}
            print "\n";
        }
    ' $x > test_A_${x}.trans1 || exit 1

done

for x in $(seq -f "%02g" 02 07); do

    $local/flist2scp_12.pl test_B_${x}.flist | sort > test_B_${x}_sph_tmp.scp || exit 1

    cat test_B_${x}_sph_tmp.scp | awk '{print $1}' \
        | $local/find_transcripts.pl dot_files.flist > test_B_${x}_tmp.trans1 || exit 1


    cat test_B_${x}_sph_tmp.scp | perl -e \
    ' $condition="$ARGV[0]";
        if ($condition eq "01") {$suffix=0;}
        elsif ($condition eq "02") {$suffix=1;} 
        elsif ($condition eq "03") {$suffix=2;} 
        elsif ($condition eq "04") {$suffix=3;} 
        elsif ($condition eq "05") {$suffix=4;} 
        elsif ($condition eq "06") {$suffix=5;} 
        elsif ($condition eq "07") {$suffix=6;} 
        elsif ($condition eq "08") {$suffix=7;} 
        elsif ($condition eq "09") {$suffix=8;} 
        elsif ($condition eq "10") {$suffix=9;} 
        elsif ($condition eq "11") {$suffix=a;} 
        elsif ($condition eq "12") {$suffix=b;} 
        elsif ($condition eq "13") {$suffix=c;} 
        elsif ($condition eq "14") {$suffix=d;} 
        else {print STDERR "error condition $condition";}
        while(<STDIN>) 
        {
            @A=split(" ", $_);  
            print $A[0].$suffix." ".$A[1]."\n";
        }
    ' $x > test_B_${x}_sph.scp || exit 1


    cat test_B_${x}_tmp.trans1 | perl -e \
    ' $condition="$ARGV[0]";
        if ($condition eq "01") {$suffix=0;}
        elsif ($condition eq "02") {$suffix=1;} 
        elsif ($condition eq "03") {$suffix=2;} 
        elsif ($condition eq "04") {$suffix=3;} 
        elsif ($condition eq "05") {$suffix=4;} 
        elsif ($condition eq "06") {$suffix=5;} 
        elsif ($condition eq "07") {$suffix=6;} 
        elsif ($condition eq "08") {$suffix=7;} 
        elsif ($condition eq "09") {$suffix=8;} 
        elsif ($condition eq "10") {$suffix=9;} 
        elsif ($condition eq "11") {$suffix=a;} 
        elsif ($condition eq "12") {$suffix=b;} 
        elsif ($condition eq "13") {$suffix=c;} 
        elsif ($condition eq "14") {$suffix=d;} 
        else {print STDERR "error condition $condition";}
        while(<STDIN>) 
        {
            @A=split(" ", $_);  
            print $A[0].$suffix;
            for ($i=1; $i < @A; $i++) {print " ".$A[$i];}
            print "\n";
        }
    ' $x > test_B_${x}.trans1 || exit 1

done

for x in 08; do

    $local/flist2scp_12.pl test_C_${x}.flist | sort > test_C_${x}_sph_tmp.scp || exit 1

    cat test_C_${x}_sph_tmp.scp | awk '{print $1}' \
        | $local/find_transcripts.pl dot_files.flist > test_C_${x}_tmp.trans1 || exit 1

    cat test_C_${x}_sph_tmp.scp | perl -e \
    ' $condition="$ARGV[0]";
        if ($condition eq "01") {$suffix=0;}
        elsif ($condition eq "02") {$suffix=1;} 
        elsif ($condition eq "03") {$suffix=2;} 
        elsif ($condition eq "04") {$suffix=3;} 
        elsif ($condition eq "05") {$suffix=4;} 
        elsif ($condition eq "06") {$suffix=5;} 
        elsif ($condition eq "07") {$suffix=6;} 
        elsif ($condition eq "08") {$suffix=7;} 
        elsif ($condition eq "09") {$suffix=8;} 
        elsif ($condition eq "10") {$suffix=9;} 
        elsif ($condition eq "11") {$suffix=a;} 
        elsif ($condition eq "12") {$suffix=b;} 
        elsif ($condition eq "13") {$suffix=c;} 
        elsif ($condition eq "14") {$suffix=d;} 
        else {print STDERR "error condition $condition";}
        while(<STDIN>)
        {
            @A=split(" ", $_);  
            print $A[0].$suffix." ".$A[1]."\n";
        }
    ' $x > test_C_${x}_sph.scp || exit 1


    cat test_C_${x}_tmp.trans1 | perl -e \
    ' $condition="$ARGV[0]";
        if ($condition eq "01") {$suffix=0;}
        elsif ($condition eq "02") {$suffix=1;} 
        elsif ($condition eq "03") {$suffix=2;} 
        elsif ($condition eq "04") {$suffix=3;} 
        elsif ($condition eq "05") {$suffix=4;} 
        elsif ($condition eq "06") {$suffix=5;} 
        elsif ($condition eq "07") {$suffix=6;} 
        elsif ($condition eq "08") {$suffix=7;} 
        elsif ($condition eq "09") {$suffix=8;} 
        elsif ($condition eq "10") {$suffix=9;} 
        elsif ($condition eq "11") {$suffix=a;} 
        elsif ($condition eq "12") {$suffix=b;} 
        elsif ($condition eq "13") {$suffix=c;} 
        elsif ($condition eq "14") {$suffix=d;} 
        else {print STDERR "error condition $condition";}
        while(<STDIN>)
        {
            @A=split(" ", $_);  
            print $A[0].$suffix;
            for ($i=1; $i < @A; $i++) {print " ".$A[$i];}
            print "\n";
        }
    ' $x > test_C_${x}.trans1 || exit 1

done

for x in $(seq -f "%02g" 09 14); do

    $local/flist2scp_12.pl test_D_${x}.flist | sort > test_D_${x}_sph_tmp.scp || exit 1

    cat test_D_${x}_sph_tmp.scp | awk '{print $1}' \
        | $local/find_transcripts.pl dot_files.flist > test_D_${x}_tmp.trans1 || exit 1


    cat test_D_${x}_sph_tmp.scp | perl -e \
    ' $condition="$ARGV[0]";
        if ($condition eq "01") {$suffix=0;}
        elsif ($condition eq "02") {$suffix=1;} 
        elsif ($condition eq "03") {$suffix=2;} 
        elsif ($condition eq "04") {$suffix=3;} 
        elsif ($condition eq "05") {$suffix=4;} 
        elsif ($condition eq "06") {$suffix=5;} 
        elsif ($condition eq "07") {$suffix=6;} 
        elsif ($condition eq "08") {$suffix=7;} 
        elsif ($condition eq "09") {$suffix=8;} 
        elsif ($condition eq "10") {$suffix=9;} 
        elsif ($condition eq "11") {$suffix=a;} 
        elsif ($condition eq "12") {$suffix=b;} 
        elsif ($condition eq "13") {$suffix=c;} 
        elsif ($condition eq "14") {$suffix=d;} 
        else {print STDERR "error condition $condition";}
        while(<STDIN>)
        {
            @A=split(" ", $_);  
           print $A[0].$suffix." ".$A[1]."\n";
        }
    ' $x > test_D_${x}_sph.scp || exit 1


    cat test_D_${x}_tmp.trans1 | perl -e \
    ' $condition="$ARGV[0]";
        if ($condition eq "01") {$suffix=0;}
        elsif ($condition eq "02") {$suffix=1;} 
        elsif ($condition eq "03") {$suffix=2;} 
        elsif ($condition eq "04") {$suffix=3;} 
        elsif ($condition eq "05") {$suffix=4;} 
        elsif ($condition eq "06") {$suffix=5;} 
        elsif ($condition eq "07") {$suffix=6;} 
        elsif ($condition eq "08") {$suffix=7;} 
        elsif ($condition eq "09") {$suffix=8;} 
        elsif ($condition eq "10") {$suffix=9;} 
        elsif ($condition eq "11") {$suffix=a;} 
        elsif ($condition eq "12") {$suffix=b;} 
        elsif ($condition eq "13") {$suffix=c;} 
        elsif ($condition eq "14") {$suffix=d;} 
        else {print STDERR "error condition $condition";}
        while(<STDIN>) 
        {
            @A=split(" ", $_);  
            print $A[0].$suffix;
            for ($i=1; $i < @A; $i++) {print " ".$A[$i];}
            print "\n";
        }
    ' $x > test_D_${x}.trans1 || exit 1

done

cat test_A_*_sph.scp | sort -k1 > test_A_sph.scp || exit 1
cat test_B_*_sph.scp | sort -k1 > test_B_sph.scp || exit 1
cat test_C_*_sph.scp | sort -k1 > test_C_sph.scp || exit 1
cat test_D_*_sph.scp | sort -k1 > test_D_sph.scp || exit 1

cat test_A_??.trans1 | sort -k1 > test_A.trans1 || exit 1
cat test_B_??.trans1 | sort -k1 > test_B.trans1 || exit 1
cat test_C_??.trans1 | sort -k1 > test_C.trans1 || exit 1
cat test_D_??.trans1 | sort -k1 > test_D.trans1 || exit 1



# Do some basic normalization steps.  At this point we don't remove OOVs--
# that will be done inside the training scripts, as we'd like to make the
# data-preparation stage independent of the specific lexicon used.
noiseword="<NOISE>";
for x in test_A test_B test_C test_D; do
    cat $x.trans1 | $local/normalize_transcript.pl $noiseword \
        | sort > $x.txt || exit 1;
done

# Create scp's with wav's. (the wv1 in the distribution is not really wav, it is sph.)
for x in  test_A test_B test_C test_D; do
    awk '{printf("%s sox -B -r 16k -e signed -b 16 -c 1 -t raw %s -t wav - |\n", $1, $2);}' < ${x}_sph.scp \
        > ${x}_wav.scp || exit 1
done

# Make the utt2spk and spk2utt files.
for x in test_A test_B test_C test_D ; do
    cat ${x}_sph.scp | awk '{print $1}' \
        | perl -ane 'chop; m:^...:; print "$_ $&\n";' > $x.utt2spk
    cat $x.utt2spk | $utils/utt2spk_to_spk2utt.pl > $x.spk2utt || exit 1;
done


echo "Data preparation succeeded"




