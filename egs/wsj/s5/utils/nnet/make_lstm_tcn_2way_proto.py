#!/usr/bin/env python

# Copyright 2015  Brno University of Technology (author: Karel Vesely)

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#  http://www.apache.org/licenses/LICENSE-2.0
#
# THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED
# WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE,
# MERCHANTABLITY OR NON-INFRINGEMENT.
# See the Apache 2 License for the specific language governing permissions and
# limitations under the License.

# Generated Nnet prototype, to be initialized by 'nnet-initialize'.

import sys

###
### Parse options
###
from optparse import OptionParser
usage="%prog [options] <feat-dim> <num-leaves> >nnet-proto-file"
parser = OptionParser(usage)
#
parser.add_option('--feat-dim1', dest='feat_dim1', type='int', default=40,
                  help='Number of LSTM input dimension1 [default: %default]');
parser.add_option('--feat-dim2', dest='feat_dim2', type='int', default=11,
                  help='Number of LSTM input dimension 2 [default: %default]');
parser.add_option('--num-cells-dim1', dest='num_cells_dim1', type='int', default=64, 
                  help='Number of LSTM cells dimension 1 [default: %default]');
parser.add_option('--num-cells-dim2', dest='num_cells_dim2', type='int', default=16, 
                  help='Number of LSTM cells dimension 2 [default: %default]');
parser.add_option('--num-recurrent-dim1', dest='num_recurrent_dim1', type='int', default=32, 
                   help='Number of LSTM recurrent units dimension 1 [default: %default]');
parser.add_option('--num-recurrent-dim2', dest='num_recurrent_dim2', type='int', default=16, 
                   help='Number of LSTM recurrent units dimension 2 [default: %default]');
parser.add_option('--num-layers', dest='num_layers', type='int', default=2, 
                   help='Number of LSTM layers [default: %default]');
parser.add_option('--lstm-stddev-factor', dest='lstm_stddev_factor', type='float', default=0.01, 
                   help='Standard deviation of initialization [default: %default]');
parser.add_option('--param-stddev-factor', dest='param_stddev_factor', type='float', default=0.04, 
                   help='Standard deviation in output layer [default: %default]');
parser.add_option('--clip-gradient', dest='clip_gradient', type='float', default=5.0, 
                   help='Clipping constant applied to gradients [default: %default]');
#
(o,args) = parser.parse_args()
if len(args) != 2 : 
  parser.print_help()
  sys.exit(1)

(feat_dim, num_leaves) = map(int,args);
assert(feat_dim == o.feat_dim1 * o.feat_dim2);

# Original prototype from Jiayu,
#<NnetProto>
#<Transmit> <InputDim> 40 <OutputDim> 40
#<LstmProjectedStreams> <InputDim> 40 <OutputDim> 512 <CellDim> 800 <ParamScale> 0.01 <NumStream> 4
#<AffineTransform> <InputDim> 512 <OutputDim> 8000 <BiasMean> 0.000000 <BiasRange> 0.000000 <ParamStddev> 0.04
#<Softmax> <InputDim> 8000 <OutputDim> 8000
#</NnetProto>

print "<NnetProto>"
# normally we won't use more than 2 layers of LSTM
if o.num_layers == 1:
    print "<LstmTcnProjectedStreamsSpeed> <InputDim> %d <OutputDim> %d <CellDim> %d <InputDim1> %d <InputDim2> %d <CellDim1> %d <CellDim2> %d <OutputDim1> %d <OutputDim2> %d <ParamScale> %f <ClipGradient> %f" % \
        (feat_dim, o.num_recurrent_dim1*o.num_recurrent_dim2, o.num_cells_dim1*o.num_cells_dim2, \
        o.feat_dim1, o.feat_dim2, o.num_cells_dim1, o.num_cells_dim2, o.num_recurrent_dim1, o.num_recurrent_dim2, \
        o.lstm_stddev_factor, o.clip_gradient)
elif o.num_layers == 2:
    print "<LstmTcnProjectedStreamsSpeed> <InputDim> %d <OutputDim> %d <CellDim> %d <InputDim1> %d <InputDim2> %d <CellDim1> %d <CellDim2> %d <OutputDim1> %d <OutputDim2> %d <ParamScale> %f <ClipGradient> %f" % \
        (feat_dim, o.num_recurrent_dim1*o.num_recurrent_dim2, o.num_cells_dim1*o.num_cells_dim2, \
        o.feat_dim1, o.feat_dim2, o.num_cells_dim1, o.num_cells_dim2, o.num_recurrent_dim1, o.num_recurrent_dim2, \
        o.lstm_stddev_factor, o.clip_gradient)
    print "<LstmTcnProjectedStreamsSpeed> <InputDim> %d <OutputDim> %d <CellDim> %d <InputDim1> %d <InputDim2> %d <CellDim1> %d <CellDim2> %d <OutputDim1> %d <OutputDim2> %d <ParamScale> %f <ClipGradient> %f" % \
        (o.num_recurrent_dim1*o.num_recurrent_dim2, o.num_recurrent_dim1*o.num_recurrent_dim2, o.num_cells_dim1*o.num_cells_dim2, \
        o.num_recurrent_dim1, o.num_recurrent_dim2, o.num_cells_dim1, o.num_cells_dim2, o.num_recurrent_dim1, o.num_recurrent_dim2, \
        o.lstm_stddev_factor, o.clip_gradient)
else:
    sys.stderr.write("make_lstm_tcn_proto.py ERROR: more than 2 layers of LSTM, not supported yet.\n")
    sys.exit(1)
print "<AffineTransform> <InputDim> %d <OutputDim> %d <BiasMean> 0.0 <BiasRange> 0.0 <ParamStddev> %f" % \
    (o.num_recurrent_dim1 * o.num_recurrent_dim2, num_leaves, o.param_stddev_factor)
print "<Softmax> <InputDim> %d <OutputDim> %d" % \
    (num_leaves, num_leaves)
print "</NnetProto>"


