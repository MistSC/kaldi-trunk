#!/bin/bash

. ./cmd.sh ## You'll want to change cmd.sh to something that will work on your system.
           ## This relates to the queue.
#Now begin train TCN systems on multi data
. ./path.sh

# training scheduler,
learn_rate=0.008
momentum=0
l1_penalty=0
l2_penalty=0.00002

#train TCN 
gmmdir=exp/tri3
dir=exp/tri5m_hybrid
ali=${gmmdir}_ali
data=data-fbank

tcn_proto=(23 11 64 16 64 16 64 16)
dnn_proto=(1024 1024 1024 1024)

echo "Layerwise pretrain hybrid training"
$cuda_cmd $dir/_train_nnet.log \
  steps/nnet/train_new.sh --network-type "hybrid_tdnn" \
    --learn-rate $learn_rate \
    --momentum $momentum \
    --l1-penalty $l1_penalty \
    --l2-penalty $l2_penalty \
    --tcn-proto-array $tcn_proto \
    --dnn-proto-array $dnn_proto \
    $data/train_tr90 $data/train_cv10 data/lang $ali $ali $dir || exit 1;

#make graph and decode for average
echo "make graph and decode"
utils/mkgraph.sh data/lang_test_bg $dir $dir/graph_test || exit 1;
steps/nnet/decode.sh --nj 16 --acwt 0.20 --config conf/decode_dnn.config \
  ${dir}/graph_test data-fbank/test $dir/decode_test || exit 1;

utils/mkgraph.sh data/lang_test_bg $dir $dir/graph_dev || exit 1;
steps/nnet/decode.sh --nj 16 --acwt 0.20 --config conf/decode_dnn.config \
  ${dir}/graph_dev data-fbank/dev $dir/decode_dev || exit 1;


