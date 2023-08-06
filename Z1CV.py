import easyocr

reader = easyocr.Reader(["ch_sim", "en"])
res = reader.readtext("Caches\\tmp.png")
print(res)