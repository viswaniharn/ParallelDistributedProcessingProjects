from pyspark import SparkContext

import sys, os, time

def to_list(a):
	return [a]

def append(a, b):
	a.append(b)
	return a

def extend(a, b):
	a.extend(b)
	return a

# Returns a key value pair with child as the key and parent as the value
def map_rdd_in(rdd):
	rdd = rdd.map(lambda x: [x[0], x[1]])
	rdd = rdd.combineByKey(to_list, append, extend)

	return rdd

# Returns a key value pair with parent as the key and list of children as the value
def map_rdd_out(rdd):
	rdd = rdd.map(lambda x: [x[1], x[0]])
	rdd = rdd.combineByKey(to_list, append, extend)

	return rdd

# Returns a key valur pair mapping a node to one level closer to the root
def reduce_rdd(rdd_in, rdd_out):
	rdd_in = rdd_out.leftOuterJoin(rdd_in)
	
	def reduce_list(x):
		out_list = []
		c = x[1][0]
		if (x[1][1] == None):
			p = x[0]

		else:
			p = x[1][1][0]
		
		for i in c:
			out_list.append((i, p))
		return out_list

	return rdd_in.flatMap(reduce_list)

start_time = time.time()

sc = SparkContext()

in_path = sys.argv[1]

out_path = sys.argv[2]

rdd = sc.textFile(in_path)

rdd = rdd.map(lambda x: (int(x.split(' ')[0]), int(x.split(' ')[1])))

prev_sum = 0

while True:

	rdd_out = map_rdd_out(rdd)
	
	rdd_in = map_rdd_in(rdd)
	
	rdd_in = reduce_rdd(rdd_in, rdd_out)
	
	rdd = rdd_in

	current_sum = rdd.map(lambda x: x[1]).sum()
	
	if prev_sum == current_sum:
		break

	prev_sum = current_sum

rdd.saveAsTextFile(out_path)

sc.stop()
print(round(time.time()-start_time,1))