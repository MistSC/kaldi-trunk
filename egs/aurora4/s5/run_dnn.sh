#!/bin/bash
. ./cmd.sh ## You'll want to change cmd.sh to something that will work on your system.
           ## This relates to the queue.

rbm=0                   # switch rbm pretrain 
expindex=tri6b_dnn      # experiment index

#Now begin train DNN systems on multi data
. ./path.sh
if [$rbm -eq 1];then
    echo "using RBM pretrain"
    #RBM pretrain
    dir=exp/${expindex}_pretrain
    $cuda_cmd $dir/_pretrain_dbn.log \
      steps/nnet/pretrain_dbn.sh --nn-depth 1 --rbm-iter 3 data-fbank/train_si84_multi $dir
    dbn=exp/${expindex}_pretrain/7.dbn
fi
dir=exp/${expindex}
ali=exp/tri2b_multi_ali_si84
ali_dev=exp/tri2b_multi_ali_dev_0330
feature_transform=exp/${expindex}_pretrain/final.feature_transform
if [$rbm -eq 1];then
    echo "RBM pretrain DNN training"
    $cuda_cmd $dir/_train_nnet.log \
      steps/nnet/train.sh --feature-transform $feature_transform --dbn $dbn --hid-layers 0 --learn-rate 0.008 \
      data-fbank/train_si84_multi data-fbank/dev_0330 data/lang $ali $ali_dev $dir || exit 1;
else 
    echo "no RBM pretrain DNN training"
    $cuda_cmd $dir/_train_nnet.log \
      steps/nnet/train.sh --hid-layers 1 --learn-rate 0.008 --network-type "dnn"\
      data-fbank/train_si84_multi data-fbank/dev_0330 data/lang $ali $ali_dev $dir || exit 1;
fi

#Make graph and decode
echo "make graph and decode for average"
utils/mkgraph.sh data/lang_test_tgpr_5k $dir $dir/graph_tgpr_5k || exit 1;
steps/nnet/decode.sh --nj 8 --acwt 0.10 --config conf/decode_dnn.config \
  ${dir}/graph_tgpr_5k data-fbank/test_eval92 $dir/decode_tgpr_5k_eval92 || exit 1;

#make graph and decode for ABCD
echo "make graph and decode for ABCD" 
for x in test_A test_B test_C test_D;do
steps/nnet/decode.sh --nj 8 --acwt 0.10 --config conf/decode_dnn.config \
  ${dir}/graph_tgpr_5k data-fbank/$x $dir/decode_tgpr_5k_$x || exit 1;
done

