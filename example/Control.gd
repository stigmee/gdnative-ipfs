extends Control

var what = 0

func _ipfs_download(ipfs_url, file):
	if not $IPFS.download(ipfs_url, file):
		print("Failed downloading " + ipfs_url + " as " + file + "! Reason: " + $IPFS.get_error())
		return false
	print("Downloaded " + ipfs_url + " as " + file)
	return true

func _load_png(file):
	$TextureRect.texture = ImageTexture.new()
	$TextureRect.texture.load(file)
	$TextureRect.set_position($TextureRect.get_position() + Vector2(16, 16))

func _download_png():
	var url = '/ipfs/QmcPZ7WdGmeDz8ZehUdF1BG8oGZADNKwkGWvgyFYAaw7Qy'
	var file = '/tmp/Stigmee.png'
	if _ipfs_download(url, file):
		return _load_png(file)
	return false

func _load_text(file):
	$TextEdit.text = ""
	var f = File.new()
	f.open(file, File.READ)
	$TextEdit.text += f.get_as_text()
	f.close()
	pass

func _download_text():
	var url = '/ipfs/QmYwAPJzv5CZsnA625s3Xf2nemtYgPpHdWEz79ojWnPbdG/readme'
	var file = '/tmp/readme.txt'
	if _ipfs_download(url, file):
		return _load_text(file)
	return false

func _on_Timer_timeout():
	what = (what + 1) % 2
	if what == 0:
		_download_png()
	else:
		_download_text()
	pass 

func _ready():
	$Timer.connect("timeout", self, "_on_Timer_timeout")
	pass

func _process(delta):
	pass
