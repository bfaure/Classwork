# Simple directory access
def print_directory_contents(path=".",indentation=""):
	import os
	items = os.listdir(path)
	for item in items:
		item_path = os.path.join(path,item)
		if os.path.isdir(item_path): print_directory_contents(item_path,indentation+"\t")
		else: print indentation+item_path

## Decorators
def timing_function(some_function):
	# outputs the time a function takes to execute
	import time
	def wrapper():
		t1 = time.time()
		some_function()
		t2 = time.time()
		return "Time it took to run the function: "+str(t2-t1)+"\n"
	return wrapper

@timing_function
def my_function():
	num_list = []
	for num in range(0,10000):
		num_list.append(num)
	print("\nSum of all the numbers: "+str(sum(num_list)))

## Binary Tree stuff
class node(object):
	def __init__(self,value,left_child=None,right_child=None,parent=None):
		self.value = value 
		self.left_child = left_child
		self.right_child = right_child
		self.parent = parent 

	def set_left_child(self,new_left):
		self.left_child = new_left
		new_left.parent = self 

	def set_right_child(self,new_right):
		self.right_child = new_right 
		new_right.parent = self

class tree(object):
	def __init__(self,root=None,root_value=None):
		if root is not None:
			self.root = root
			self.root.parent = None
		else:
			self.root = node(root_value)

def print_tree_dfs(tree_object):
	root = tree_object.root
	def dfs(node):
		left_child = node.left_child
		right_child = node.right_child 
		if left_child is not None:
			dfs(left_child)
		if right_child is not None:
			dfs(right_child)
		print(node.value)
	dfs(root)

def print_tree_bfs(tree_object):
	root = tree_object.root 
	queue = []
	queue.append(root)
	while True:
		if len(queue)==0:
			return
		cur = queue[0]
		del queue[0]
		print (cur.value)

		if cur.left_child is not None:
			queue.append(cur.left_child)
		if cur.right_child is not None:
			queue.append(cur.right_child) 

def search_tree_dfs(tree_object,target):
	root = tree_object.root
	def dfs(node,height):
		left_child 	= node.left_child 
		right_child = node.right_child
		found_left_height,found_right_height 	= -1,-1
		found_left,found_right 					= -1,-1

		if left_child is not None: 	found_left,found_left_height =  dfs(left_child,height+1)
		if right_child is not None: found_right,found_right_height =  dfs(right_child,height+1)

		if found_left==1: 		return 1,found_left_height
		if found_right==1: 		return 1,found_right_height
		if node.value==target: 	return 1, height 
		return -1,-1

	found,height = dfs(root,height=0)
	if found: print("Found target at height "+str(height))
	else: print("Did not find target")

def search_tree_bfs(tree_object,target):
	root = tree_object.root 
	queue = []
	queue.append([root,0])
	while True:
		if len(queue)==0:
			print("Did not find target")
			return

		cur,cur_height = queue[0]
		del queue[0]

		if cur.value==target:
			print("Found target at height "+str(cur_height))
			return

		if cur.left_child is not None: queue.append([cur.left_child,cur_height+1])
		if cur.right_child is not None: queue.append([cur.right_child,cur_height+1]) 

def construct_default_tree():
	l1 = node(40)
	l2 = node(65)
	l3 = node(55)
	l4 = node(93)

	m1 = node(85)
	m2 = node(80)

	u1 = node(90)

	u1.set_left_child(m1)
	u1.set_right_child(m2)

	m1.set_left_child(l1)
	m1.set_right_child(l2)
	m2.set_left_child(l3)
	m2.set_right_child(l4)

	t = tree(u1)
	return t

def find_maximum_egg_drop_height(max_height=12,building_height=100):
	def helper(max_height,building_height):
		egg1_OK, egg2_OK = True,True 
		step_size = 10
		for i in range(0,building_height,step_size):
			if i==max_height:
				return max_height
			if i >= max_height:
				for j in range(i*step_size,i*step_size+step_size):
					if j == max_height:
						return max_height
	import time
	start_time = time.time()
	max_height = helper(max_height,building_height)
	print("max_height = "+str(max_height)+" "+str(time.time()-start_time)+" seconds")


def reverse_linked_list(head):
	from copy import copy 
	last = None 
	cur = head
	while True:
		if cur==None:
			break
		temp = copy(cur.next)
		cur.next = last
		cur = temp
	print("Finished reversing linked list")
	return cur 


# main
def main():
	#print_directory_contents("WikiClassify2.0")
	#print(my_function())
	#t = construct_default_tree()
	#print_tree_dfs(t)

	find_maximum_egg_drop_height()




if __name__ == '__main__':
	main()