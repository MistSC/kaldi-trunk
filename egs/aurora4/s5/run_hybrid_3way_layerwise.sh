#!/bin/bash

. ./cmd.sh ## You'll want to change cmd.sh to something that will work on your system.
           ## This relates to the queue.
#Now begin train TCN systems on multi data
. ./path.sh

# training scheduler
learn_rate=0.004
momentum=0
l1_penalty=0    # 0.0000005
l2_penalty=0

# train TCN 
dir=exp/tri9a_hybrid
ali=exp/tri2b_multi_ali_si84
ali_dev=exp/tri2b_multi_ali_dev_0330

# network topology
tcn_proto=(40 11 1 32 16 2 32 16 2 32 16 2)
dnn_proto=(1024 1024 1024 1024)

echo "Layerwise pretrain 3 way hybrid training"
$cuda_cmd $dir/_train_nnet.log \
  steps/nnet/train_new.sh --network-type "hybrid_tdnn_3w" \
    --learn-rate $learn_rate \
    --momentum $momentum \
    --l1-penalty $l1_penalty \
    --l2-penalty $l2_penalty \
    --tcn-proto-array $tcn_proto \
    --dnn-proto-array $dnn_proto \
    data-fbank/train_si84_multi data-fbank/dev_0330 data/lang $ali $ali_dev $dir || exit 1;

#make graph and decode for average
utils/mkgraph.sh data/lang_test_tgpr_5k $dir $dir/graph_tgpr_5k || exit 1;
steps/nnet/decode.sh --nj 8 --acwt 0.10 --config conf/decode_dnn.config \
  ${dir}/graph_tgpr_5k data-fbank/test_eval92 $dir/decode_tgpr_5k_eval92 || exit 1;

#make graph and decode for ABCD
for x in test_A test_B test_C test_D;do
steps/nnet/decode.sh --nj 8 --acwt 0.10 --config conf/decode_dnn.config \
  ${dir}/graph_tgpr_5k data-fbank/$x $dir/decode_tgpr_5k_$x || exit 1;
done


# DNN Sequential DT training
#......
