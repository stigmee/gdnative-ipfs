extends Spatial

# Get a file
func _ready():
	var url = '/ipfs/QmYwAPJzv5CZsnA625s3Xf2nemtYgPpHdWEz79ojWnPbdG/readme'
	var file = '/tmp/readme.txt'
	if not $IPFS.get_file(url, file):
		print("IPFS failed")
	pass 
