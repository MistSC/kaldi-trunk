#!/usr/bin/env python

# Generated Nnet prototype, to be initialized by 'nnet-initialize'.

import math, random, sys
from optparse import OptionParser

###
### Parse options
###
usage="%prog [options] <feat-dim> <num-leaves> <num-hidden-layers> ( <layer1_dim1> <layer1_dim2>... ) >nnet-proto-file"
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
#parser.add_option('--num-dim-in', dest='',
#                    help='input dimension in ',
#                    default=0, type='int');


(o,args) = parser.parse_args()


if len(args) != 3 + int(args[2]) * 2 or (len(args) - 3) % 2!=0 :
  print "hiddeb layers number can not fix dim args"
  parser.print_help()
  sys.exit(1)
(feat_dim, num_leaves, num_hid_layers) = map(int,args[0:3]);

list_each_layer_dim = map(int,args[3:]); 


#(feat_dim, num_leaves, num_hid_layers, num_hid_neurons) = map(int,args);
### End parse options

# Check

# In this situation must have >=2 hidden layers(1 for projection layer and others for hidden layers)
assert(num_hid_layers > 1)
assert(feat_dim > 0)
assert(num_leaves > 0)
assert(num_hid_layers >= 0)
assert(feat_dim == list_each_layer_dim[0] * list_each_layer_dim[1])

# make TCN prototype

# Begin the prototype,
print "<NnetProto>"

# First TCN component
print "<TCNComponent> <InputDim> %d <OutputDim> %d <BiasMean> %f <BiasRange> %f <ParamStddev> %f <InputDim1> %d <InputDim2> %d <OutputDim1> %d <OutputDim2> %d" % \
       (feat_dim, list_each_layer_dim[2]*list_each_layer_dim[3],\
       o.hid_bias_mean, o.hid_bias_range, o.param_stddev_factor, \
       list_each_layer_dim[0], list_each_layer_dim[1],\
       list_each_layer_dim[2],list_each_layer_dim[3])
       
#print "<InputDim1> %d <InputDim2> %d" % (list_each_layer_dim[0],list_each_layer_dim[1])
#print "<OutputDim1> %d <OutputDim2> %d" % (list_each_layer_dim[2],list_each_layer_dim[3])
print "%s <InputDim> %d <OutputDim> %d" % \
        (o.activation_type, list_each_layer_dim[2]*list_each_layer_dim[3], list_each_layer_dim[2]*list_each_layer_dim[3])

# Internal TCN component
for i in range(1,num_hid_layers-1):
    print "<TCNComponent> <InputDim> %d <OutputDim> %d <BiasMean> %f <BiasRange> %f <ParamStddev> %f <InputDim1> %d <InputDim2> %d <OutputDim1> %d <OutputDim2> %d" % \
           (list_each_layer_dim[2*i]*list_each_layer_dim[2*i+1], list_each_layer_dim[2*(i+1)]*list_each_layer_dim[2*(i+1)+1], \
           o.hid_bias_mean, o.hid_bias_range, o.param_stddev_factor, \
           list_each_layer_dim[2*i], list_each_layer_dim[2*i+1], list_each_layer_dim[2*(i+1)],list_each_layer_dim[2*(i+1)+1])
    #print "<InputDim1> %d <InputDim2> %d" % (list_each_layer_dim[2*i],list_each_layer_dim[2*i+1])
    #print "<OutputDim1> %d <OutputDim2> %d" % (list_each_layer_dim[2*(i+1)],list_each_layer_dim[2*(i+1)+1])
    print "%s <InputDim> %d <OutputDim> %d" % \
        (o.activation_type, list_each_layer_dim[2*(i+1)]*list_each_layer_dim[2*(i+1)+1], list_each_layer_dim[2*(i+1)]*list_each_layer_dim[2*(i+1)+1])

# Last TCN projection component
print "<TCNProjectionComponent> <InputDim> %d <OutputDim> %d <BiasMean> %f <BiasRange> %f <ParamStddev> %f <InputDim1> %d <InputDim2> %d" % \
    (list_each_layer_dim[-2]*list_each_layer_dim[-1], num_leaves, \
    o.hid_bias_mean, o.hid_bias_range, o.param_stddev_factor,\
    list_each_layer_dim[-2], list_each_layer_dim[-1])
    
# Optionaly append softmax
print "<Softmax> <InputDim> %d <OutputDim> %d" % (num_leaves, num_leaves)

# End the prototype
print "</NnetProto>"

# We are done!
sys.exit(0)




    



    







