#!/usr/bin/env python

# Generated Nnet prototype, to be initialized by 'nnet-initialize'.

import math, random, sys
from optparse import OptionParser

###
### Parse options
###
usage="%prog [options] <feat-dim> <num-leaves> <num-hidden-layers> ( <layer1_dim1> <layer1_dim2> <layer1_dim3>... ) >nnet-proto-file"
parser = OptionParser(usage)

parser.add_option('--activation-type', dest='activation_type',
                    help='Select type of activation function : (<Sigmoid>|<Tanh>) [default: %default]',
                    default='<Sigmoid>', type='string');
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

index_tcn = args.index('tcn')
index_dnn = args.index('dnn')

assert(index_tcn<=index_dnn or index_tcn!=3)

(feat_dim, num_leaves, num_hid_layers) = map(int,args[0:3])
list_tcn_layer_dim = map(int,args[index_tcn+1:index_dnn])
list_dnn_layer_dim = map(int,args[index_dnn+1:])
assert(len(list_tcn_layer_dim)%3==0)
num_tcn_layers = len(list_tcn_layer_dim)/3-1
if num_tcn_layers<0:
  num_tcn_layers=0
num_dnn_layers = len(list_dnn_layer_dim)

#if num_dnn_layers==0:
list_dnn_layer_dim.append(num_leaves)
if num_tcn_layers>0 and num_dnn_layers==0:      # only tcn layers
  assert(list_dnn_layer_dim[-1]==num_leaves)
elif num_tcn_layers>0 and num_dnn_layers!=0:    # tcn and dnn layers
  assert(list_dnn_layer_dim[0]==list_tcn_layer_dim[-3]*list_tcn_layer_dim[-2]*list_tcn_layer_dim[-1])
  assert(list_dnn_layer_dim[-1]==num_leaves)
elif num_tcn_layers<=0:                         # only dnn layers
  assert(list_dnn_layer_dim[0]==feat_dim)
  assert(list_dnn_layer_dim[-1]==num_leaves)
### End parse options

# Check

assert(num_hid_layers >= 1)
assert(feat_dim > 0)
assert(num_leaves > 0)
assert(num_tcn_layers + num_dnn_layers == num_hid_layers)

### make TCN prototype

# Begin the prototype,
print "<NnetProto>"

if num_tcn_layers!=0:
  # First TCN component
  print "<TCN3WayComponent> <InputDim> %d <OutputDim> %d <BiasMean> %f <BiasRange> %f <ParamStddev> %f <InputDim1> %d <InputDim2> %d  <InputDim3> %d <OutputDim1> %d <OutputDim2> %d <OutputDim3> %d" % \
       (feat_dim, list_tcn_layer_dim[3]*list_tcn_layer_dim[4]*list_tcn_layer_dim[5], \
       o.hid_bias_mean, o.hid_bias_range, o.param_stddev_factor, \
       list_tcn_layer_dim[0], list_tcn_layer_dim[1], list_tcn_layer_dim[2], \
       list_tcn_layer_dim[3], list_tcn_layer_dim[4], list_tcn_layer_dim[5])
  print "%s <InputDim> %d <OutputDim> %d" % \
        (o.activation_type, list_tcn_layer_dim[3]*list_tcn_layer_dim[4]*list_tcn_layer_dim[5], list_tcn_layer_dim[3]*list_tcn_layer_dim[4]*list_tcn_layer_dim[5])

  # Internal TCN component
  for i in range(1,num_tcn_layers-1):
    print "<TCN3WayComponent> <InputDim> %d <OutputDim> %d <BiasMean> %f <BiasRange> %f <ParamStddev> %f <InputDim1> %d <InputDim2> %d <InputDim3> %d <OutputDim1> %d <OutputDim2> %d <OutputDim3> %d" % \
           (list_tcn_layer_dim[3*i]*list_tcn_layer_dim[3*i+1]*list_tcn_layer_dim[3*i+2], list_tcn_layer_dim[3*(i+1)]*list_tcn_layer_dim[3*(i+1)+1]*list_tcn_layer_dim[3*(i+1)+2], \
           o.hid_bias_mean, o.hid_bias_range, o.param_stddev_factor, \
           list_tcn_layer_dim[3*i], list_tcn_layer_dim[3*i+1], list_tcn_layer_dim[3*i+2], \
           list_tcn_layer_dim[3*(i+1)],list_tcn_layer_dim[3*(i+1)+1],list_tcn_layer_dim[3*(i+1)+2])
    print "%s <InputDim> %d <OutputDim> %d" % \
        (o.activation_type, list_tcn_layer_dim[2*(i+1)]*list_tcn_layer_dim[2*(i+1)+1]*list_tcn_layer_dim[2*(i+1)+2], \
        list_tcn_layer_dim[2*(i+1)]*list_tcn_layer_dim[2*(i+1)+1]*list_tcn_layer_dim[2*(i+1)+2])

  # TCN projection component
  if num_hid_layers!=1:
    print "<TCN3WayProjectionComponent> <InputDim> %d <OutputDim> %d <BiasMean> %f <BiasRange> %f <ParamStddev> %f <InputDim1> %d <InputDim2> %d <InputDim3> %d" % \
      (list_tcn_layer_dim[-6]*list_tcn_layer_dim[-5]*list_tcn_layer_dim[-4], list_dnn_layer_dim[0], \
      o.hid_bias_mean, o.hid_bias_range, o.param_stddev_factor,\
      list_tcn_layer_dim[-6],list_tcn_layer_dim[-5], list_tcn_layer_dim[-4])
  elif num_hid_layers==1:
    print "<TCN3WayProjectionComponent> <InputDim> %d <OutputDim> %d <BiasMean> %f <BiasRange> %f <ParamStddev> %f <InputDim1> %d <InputDim2> %d <InputDim3> %d" % \
      (list_tcn_layer_dim[-3]*list_tcn_layer_dim[-2]*list_tcn_layer_dim[-1], list_dnn_layer_dim[0], \
      o.hid_bias_mean, o.hid_bias_range, o.param_stddev_factor,\
      list_tcn_layer_dim[-3],list_tcn_layer_dim[-2], list_tcn_layer_dim[-1])
  if num_dnn_layers!=0:
    print "%s <InputDim> %d <OutputDim> %d" % \
      (o.activation_type, list_dnn_layer_dim[0], list_dnn_layer_dim[0])


# Append DNN component
if num_dnn_layers!=0:
  for i in range(0,num_dnn_layers):
    print "<AffineTransform> <InputDim> %d <OutputDim> %d <BiasMean> %f <BiasRange> %f <ParamStddev> %f" % \
      (list_dnn_layer_dim[i],list_dnn_layer_dim[i+1],\
      o.hid_bias_mean, o.hid_bias_range, o.param_stddev_factor)
    if i!=num_dnn_layers-1:
      print "%s <InputDim> %d <OutputDim> %d" % \
        (o.activation_type, list_dnn_layer_dim[i+1], list_dnn_layer_dim[i+1])

# Optionaly append softmax
print "<Softmax> <InputDim> %d <OutputDim> %d" % (num_leaves, num_leaves)

### End the prototype
print "</NnetProto>"

# We are done!
sys.exit(0)




    



    







