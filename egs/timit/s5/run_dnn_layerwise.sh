#!/bin/bash

# This example 

. ./cmd.sh ## You'll want to change cmd.sh to something that will work on your system.
           ## This relates to the queue.

. ./path.sh ## Source the tools/utils (import the queue.pl)


gmmdir=exp/tri3
dir=exp/test1
ali=${gmmdir}_ali
data=data-fbank


# Train DNN with layerwise pretrain
echo "Layerwise pretrain DNN training"
$cuda_cmd $dir/log/train_nnet.log \
  steps/nnet/train_new.sh --hid-layers 2 --learn-rate 0.008 --network-type "dnn" \
  $data/train_tr90 $data/train_cv10 data/lang $ali $ali $dir || exit 1;

# Make graph and decode
echo "make graph and decode"
utils/mkgraph.sh data/lang_test_bg $dir $dir/graph_test || exit 1;
steps/nnet/decode.sh --nj 1 --acwt 0.20 --config conf/decode_dnn.config \
  ${dir}/graph_test data-fbank/test $dir/decode_test || exit 1;

utils/mkgraph.sh data/lang_test_bg $dir $dir/graph_dev || exit 1;
steps/nnet/decode.sh --nj 1 --acwt 0.20 --config conf/decode_dnn.config \
  ${dir}/graph_dev data-fbank/dev $dir/decode_dev || exit 1;




