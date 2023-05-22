import csv
from xml.etree import ElementTree as tree
import math
import os
path_xml= "/home/mbasa/Downloads/4113/xml"
#path_xml= "/home/mbasa/Downloads/4113/semi-auto-image-annotation-tool/annotations/annotations_voc"
csv_f= open("train_annotation.csv",'w',encoding='utf-8')
csv_w= csv.writer(csv_f)
c=0
train_t= "TRAINING"
validate_t= "VALIDATION"
test_t="TEST"
d=""
count=0
for xmls in os.listdir(path_xml):
	xml= tree.parse(path_xml+'/'+xmls)
	root= xml.getroot()
	c=0
	path= root.find('path').text
	for object in xml.findall("object"):
		if (count<300):
			name= object.find('name').text
			#print(name)
			#bndbox= object.get('bndbox')
			xmin= object[4][0].text
			if int(xmin)<0:
				xmin=0
			#xmin=bndbox.find('xmin').text
			#print(xmin)
			ymin= object[4][1].text
			if int(ymin)<0:
				ymin=0
			xmax= object[4][2].text
			if int(xmax)>500:
				xmax=500
			ymax= object[4][3].text
			if int(ymax)>375:
				ymax=375
			csv_l= [train_t,path, name, xmin, ymin, d, d, xmax, ymax]
			csv_w.writerow(csv_l)
			count=count+1
			c=1
		elif (count>300 and count<400):
			name= object.find('name').text
                     	#print(name)
                        #bndbox= object.get('bndbox')
			xmin= object[4][0].text
			if int(xmin)<0:
				xmin=0
                        #xmin=bndbox.find('xmin').text
                        #print(xmin)
			ymin= object[4][1].text
			if int(ymin)<0:
				ymin=0
			xmax= object[4][2].text
			if int(xmax)>500:
				xmax=500
			ymax= object[4][3].text
			if int(ymax)>375:
				ymax=375
			csv_l= [validate_t,path, name, xmin, ymin, d, d, xmax, ymax]
			csv_w.writerow(csv_l)
			count=count+1
			c=1
		else:
			name= object.find('name').text
                        #print(name)
                        #bndbox= object.get('bndbox')
			xmin= object[4][0].text
			if int(xmin)<0:
				xmin=0
                       	#xmin=bndbox.find('xmin').text
                        #print(xmin)
			ymin= object[4][1].text
			if int(ymin)<0:
				ymin=0
			xmax= object[4][2].text
			if int(xmax) >500:
				xmax=500
			ymax= object[4][3].text
			if int(ymax)>375:
				ymax=375
			csv_l= [test_t,path, name, xmin, ymin, d, d, xmax, ymax]
			csv_w.writerow(csv_l)
			count=count+1
			c=1


	if (c==0):
		print(c)
		csv_l=[train_t,path]
		csv_w.writerow(csv_l)
csv_f.close()
