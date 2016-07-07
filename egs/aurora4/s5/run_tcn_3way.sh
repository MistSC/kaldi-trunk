#!/bin/bash

. ./cmd.sh ## You'll want to change cmd.sh to something that will work on your system.
           ## This relates to the queue.
#Now begin train TCN systems on multi data
. ./path.sh


#train TCN 
dir=exp/test1
ali=exp/tri2b_multi_ali_si84
ali_dev=exp/tri2b_multi_ali_dev_0330
feats=data
#feature_transform=exp/tri3a_dnn_pretrain/final.feature_transform
#dbn=exp/tri3a_dnn_pretrain/7.dbn
$cuda_cmd $dir/_train_nnet.log \
  steps/nnet/train.sh --learn-rate 0.01 --network-type "tcn_3way" \
    --apply-outer-product 'true' \
    $feats/train_si84_multi $feats/dev_0330 data/lang $ali $ali_dev $dir || exit 1;

#make graph and decode for average
utils/mkgraph.sh data/lang_test_tgpr_5k $dir $dir/graph_tgpr_5k || exit 1;
steps/nnet/decode.sh --nj 8 --acwt 0.10 --config conf/decode_dnn.config \
  --apply-outer-product 'true' \
  ${dir}/graph_tgpr_5k $feats/test_eval92 $dir/decode_tgpr_5k_eval92 || exit 1;

##make graph and decode for ABCD
#for x in test_A test_B test_C test_D;do
#steps/nnet/decode.sh --nj 8 --acwt 0.10 --config conf/decode_dnn.config \
#  ${dir}/graph_tgpr_5k data-fbank/$x $dir/decode_tgpr_5k_$x || exit 1;
#done


