#!/bin/bash
. ./cmd.sh ## You'll want to change cmd.sh to something that will work on your system.
           ## This relates to the queue.

. ./path.sh


#Now begin train TCN
gmmdir=exp/tri3
dir=exp/tcn_lw_1
ali=${gmmdir}_ali
data=data-fbank

echo "Layerwise pretrain TCN training"
$cuda_cmd $dir/_train_nnet.log \
  steps/nnet/train_new.sh --hid-layers 4 --learn-rate 0.008 --network-type "tcn" \
  $data/train_tr90 $data/train_cv10 data/lang $ali $ali $dir || exit 1;

# Make graph and decode
echo "make graph and decode"
utils/mkgraph.sh data/lang_test_bg $dir $dir/graph_test || exit 1;
steps/nnet/decode.sh --nj 16 --acwt 0.20 --config conf/decode_dnn.config \
  ${dir}/graph_test data-fbank/test $dir/decode_test || exit 1;

utils/mkgraph.sh data/lang_test_bg $dir $dir/graph_dev || exit 1;
steps/nnet/decode.sh --nj 16 --acwt 0.20 --config conf/decode_dnn.config \
  ${dir}/graph_dev data-fbank/dev $dir/decode_dev || exit 1;

