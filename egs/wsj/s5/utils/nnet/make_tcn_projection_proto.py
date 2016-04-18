#!/usr/bin/env python


import math, random, sys, re

###
### Parse options
###
from optparse import OptionParser
usage="%prog [options] <in-dim1> <in-dim2> <out-dim> <hid_dim> >nnet-proto-file"
parser = OptionParser(usage)

parser.add_option('--activation-type', dest='activation_type',
                    help='Select type of activation function : (Sigmoid|Tanh) [default: %default]',
                    default='Softmax', type='string');
parser.add_option('--hid-bias-mean', dest='hid_bias_mean',
                    help='Set bias for hidden activations [default: %default]',
                    default=-2.0, type='float');
parser.add_option('--hid-bias-range', dest='hid_bias_range',
                    help='Set bias range for hidden activations (+/- 1/2 range around mean) [default: %default]',
                    default=4.0, type='float');
parser.add_option('--param-stddev-factor', dest='param_stddev_factor',
                    help='Factor to rescale Normal distriburtion for initalizing weight matrices [default: %default]',
                    default=0.1, type='float');

(o,args) = parser.parse_args()
if len(args) != 4 : 
  parser.print_help()
  sys.exit(1)
  
(in_dim1, in_dim2, out_dim, hid_dim) = map(int,args);
### End parse options 


# Check
assert(in_dim1 > 0)
assert(in_dim2 > 0)
assert(out_dim > 0)
assert(hid_dim > 0)


### Print prototype of the network
# Print header
print "<NnetProto>"

# Print component type
print "<TCNProjectionComponent> <InputDim> %d <OutputDim> %d <BiasMean> %f <BiasRange> %f <ParamStddev> %f <InputDim1> %d <InputDim2> %d" % \
  (in_dim1*in_dim2, hid_dim, o.hid_bias_mean, o.hid_bias_range, o.param_stddev_factor, in_dim1, in_dim2)

# Print activation
print "<Sigmoid> <InputDim> %d <OutputDim> %d" % \
  (hid_dim, hid_dim)

# Print affine
print "<AffineTransform> <InputDim> %d <OutputDim> %d <BiasMean> %f <BiasRange> %f <ParamStddev> %f" % \
  (hid_dim, out_dim, o.hid_bias_mean, o.hid_bias_range, o.param_stddev_factor)

# Print activation
print "<%s> <InputDim> %d <OutputDim> %d" % \
  (o.activation_type, out_dim, out_dim)

# End the prototype
print "</NnetProto>"

# We are done!
sys.exit(0)

