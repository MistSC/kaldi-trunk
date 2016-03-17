#!/bin/bash

. ./cmd.sh
. ./path.sh

nnet_proto=nnet.proto
#nnet_init=nnet.init
num_in=5
num_out=5
num_layer=1
num_neuron=10
../utils/nnet/make_nnet_proto.py $num_in $num_out $num_layer $num_neuron >$nnet_proto
nnet-initialize --binary=false $nnet_proto nnet1.nnet

nnet-remove-component --binary=false nnet1.nnet 0 nnet1.nnet
nnet-remove-component --binary=false nnet1.nnet 0 nnet1.nnet

#../utils/nnet/make_one_layer_proto.py $num_out $num_out >nnet1.proto
../utils/nnet/make_nnet_proto.py $num_neuron $num_out 1 $num_neuron >nnet1.proto
nnet-initialize --binary=false nnet1.proto nnet3.init

nnet-concat --binary=false nnet1.nnet nnet3.init nnet4.init
