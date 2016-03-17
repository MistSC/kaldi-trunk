#!/usr/bin/env python

# Generated Nnet prototype, to be initialized by 'nnet-initialize'.

import math, random, sys, re

###
### Parse options
###
from optparse import OptionParser
usage="%prog [options] <in-dim> <out-dim> >nnet-proto-file"
parser = OptionParser(usage)

parser.add_option('--activation-type', dest='activation_type',
                    help='Select type of activation function : (Sigmoid|Tanh) [default: %default]',
                    default='Sigmoid', type='string');

(o,args) = parser.parse_args()
if len(args) != 2 : 
  parser.print_help()
  sys.exit(1)
  
(in_dim, out_dim) = map(int,args);
### End parse options 


# Check
assert(in_dim > 0)
assert(out_dim > 0)



### Print prototype of the network
# Print header
print "<NnetProto>"

# Print component type
print "<%s> <InputDim> %d <OutputDim> %d" % \
(o.activation_type, in_dim, out_dim)

# End the prototype
print "</NnetProto>"

# We are done!
sys.exit(0)

