#/bin/bash

# Copyright 2015  Brno University of Technology (Author: Karel Vesely)
# Apache 2.0

# This example script trains a LSTM network on FBANK features.
# The LSTM code comes from Yiayu DU, and Wei Li, thanks!

# Note: With DNNs in RM, the optimal LMWT is 2-6. Don't be tempted to try acwt's like 0.2, 
# the value 0.1 is better both for decoding and sMBR.

. ./cmd.sh
. ./path.sh

. utils/parse_options.sh || exit 1;

# Train the DNN optimizing per-frame cross-entropy.
dir=exp/tri10test_lstm
ali=exp/tri2b_multi_ali_si84
ali_dev=exp/tri2b_multi_ali_dev_0330

# Train
$cuda_cmd $dir/_train_nnet.log \
  steps/nnet/train.sh --network-type lstm --learn-rate 0.0001 \
    --cmvn-opts "--norm-means=false --norm-vars=false" --feat-type plain --splice 0 \
    --scheduler-opts "--momentum 0.9 --halving-factor 0.5" \
    --train-tool "nnet-train-lstm-streams" \
    --train-tool-opts "--num-stream=4 --targets-delay=5" \
    --proto-opts "--num-cells 2048 --num-recurrent 1024 --num-layers 2 --clip-gradient 5.0" \
  data-fbank/train_si84_multi data-fbank/dev_0330 data/lang $ali $ali_dev $dir || exit 1;

# Make graph and decode (reuse HCLG graph) for average
utils/mkgraph.sh data/lang_test_tgpr_5k $dir $dir/graph_tgpr_5k || exit 1;
steps/nnet/decode.sh --nj 8 --acwt 0.10 --config conf/decode_dnn.config \
  ${dir}/graph_tgpr_5k data-fbank/test_eval92 $dir/decode_tgpr_5k_eval92 || exit 1;

# Make graph and decode for ABCD
for x in test_A test_B test_C test_D;do
steps/nnet/decode.sh --nj 8 --acwt 0.10 --config conf/decode_dnn.config \
  ${dir}/graph_tgpr_5k data-fbank/$x $dir/decode_tgpr_5k_$x || exit 1;
done

echo Success
exit 0

# Getting results [see RESULTS file]
# for x in exp/*/decode*; do [ -d $x ] && grep WER $x/wer_* | utils/best_wer.sh; done
