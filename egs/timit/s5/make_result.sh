#!/bin/bash
for x in exp/{mono,tri,sgmm,dnn,combine,tcn}*/decode*; do [ -d $x ] && echo $x | grep "${1:-.*}" >/dev/null && grep WER $x/wer_* 2>/dev/null | utils/best_wer.sh; done >>RESULT_1
for x in exp/{mono,tri,sgmm,dnn,combine,tcn}*/decode*; do [ -d $x ] && echo $x | grep "${1:-.*}" >/dev/null && grep Sum $x/score_*/*.sys 2>/dev/null | utils/best_wer.sh; done >>RESULT_2
exit 0
