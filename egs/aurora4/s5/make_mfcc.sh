#!/bin/bash

. ./cmd.sh ## You'll want to change cmd.sh to something that will work on your system.
           ## This relates to the queue.

# This is a shell script, but it's recommended that you run the commands one by
# one by copying and pasting into the shell.

#clean LDC wsj0 corpus available in CLSP server: /export/corpora5/LDC/LDC93S6B
#aurora4 directory in CLSP server: /export/corpora5/AURORA

##aurora4=/mnt/spdb/aurora4
#aurora4=/media/datasets/aurora4
##we need lm, trans, from WSJ0 CORPUS
##wsj0=/mnt/spdb/wall_street_journal
#wsj0=/media/datasets/wsj0ex

#local/aurora4_data_prep.sh $aurora4 $wsj0

#local/wsj_prepare_dict.sh || exit 1;

#utils/prepare_lang.sh data/local/dict "<SPOKEN_NOISE>" data/local/lang_tmp data/lang || exit 1;

#local/aurora4_format_data.sh || exit 1;

# Now make MFCC features.
# mfccdir should be some place with a largish disk where you
# want to store MFCC features.
mfccdir=mfcc

#make MFCC features for average
echo "make MFCC features for average"
for x in train_si84_clean train_si84_multi test_eval92 test_0166 dev_0330 dev_1206; do 
 steps/make_mfcc.sh  --nj 8 \
   data/$x exp/make_mfcc/$x $mfccdir || exit 1;
 steps/compute_cmvn_stats.sh data/$x exp/make_mfcc/$x $mfccdir || exit 1;
done

#make MFCC features for ABCD
echo "make MFCC features for ABCD"
for x in test_A test_B test_C test_D; do
  steps/make_mfcc.sh  --nj 8 \
    data/$x exp/make_mfcc/$x $mfccdir || exit 1;
  steps/compute_cmvn_stats.sh data/$x exp/make_mfcc/$x $mfccdir || exit 1;
done
echo "succeeded in makeing MFCC "
