#!/bin/bash

. ./cmd.sh ## You'll want to change cmd.sh to something that will work on your system.
           ## This relates to the queue.

# This is a shell script, but it's recommended that you run the commands one by
# one by copying and pasting into the shell.

#clean LDC wsj0 corpus available in CLSP server: /export/corpora5/LDC/LDC93S6B
#aurora4 directory in CLSP server: /export/corpora5/AURORA


steps/train_lda_mllt.sh \
   --splice-opts "--left-context=3 --right-context=3" \
   2500 15000 data/train_si84_multi data/lang exp/tri1_multi_ali_si84 exp/tri2b_multi || exit 1;


utils/mkgraph.sh data/lang_test_tgpr_5k exp/tri2b_multi exp/tri2b_multi/graph_tgpr_5k || exit 1;
steps/decode.sh --nj 8 \
  exp/tri2b_multi/graph_tgpr_5k data/test_eval92 exp/tri2b_multi/decode_tgpr_5k_eval92 || exit 1;

# Align tri2b system with si84 multi-condition data.
steps/align_si.sh  --nj 10 \
  --use-graphs true data/train_si84_multi data/lang exp/tri2b_multi exp/tri2b_multi_ali_si84  || exit 1;

steps/align_si.sh  --nj 10 \
  data/dev_0330 data/lang exp/tri2b_multi exp/tri2b_multi_ali_dev_0330 || exit 1;

steps/align_si.sh  --nj 10 \
  data/dev_1206 data/lang exp/tri2b_multi exp/tri2b_multi_ali_dev_1206 || exit 1;


