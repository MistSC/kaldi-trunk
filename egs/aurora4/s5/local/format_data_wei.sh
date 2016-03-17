#!/bin/bash

. ./path.sh || exit 1;

echo "Preparing test A_B_C_D data"
srcdir=data/local/data/test_4sets
cp data/local/data/spk2gender data/local/data/dot_files.flist data/local/data/test_4sets
for x in test_A test_B test_C test_D ; do 
    mkdir -p data/$x
    cp $srcdir/${x}_wav.scp data/$x/wav.scp || exit 1;
    cp $srcdir/$x.txt data/$x/text || exit 1;
    cp $srcdir/$x.spk2utt data/$x/spk2utt || exit 1;
    cp $srcdir/$x.utt2spk data/$x/utt2spk || exit 1;
    utils/filter_scp.pl data/$x/spk2utt $srcdir/spk2gender > data/$x/spk2gender || exit 1;
done

echo "Succeeded in formatting data."
