#!/bin/bash

# This example 

. ./cmd.sh ## You'll want to change cmd.sh to something that will work on your system.
           ## This relates to the queue.

. ./path.sh ## Source the tools/utils (import the queue.pl)



# Make fbank feature
fbankdir=fbank
mkdir -p data-fbank
for x in train dev test; do
  cp -r data/$x data-fbank/$x
  steps/make_fbank.sh --nj 10 \
    data-fbank/$x exp/make_fbank/$x $fbankdir || exit 1;
done

# split the data : 90% train 10% cross-validation (held-out)
utils/subset_data_dir_tr_cv.sh data-fbank/train data-fbank/train_tr90 data-fbank/train_cv10 || exit 1

