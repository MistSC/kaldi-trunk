for x in exp/{mono,tri,sgmm,nnet}*/decode*;do 
    [ -d $x ] && grep WER $x/wer_* | utils/best_wer.sh; done >>RESULT_1

