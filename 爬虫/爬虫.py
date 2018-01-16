#《爬虫0》
import urllib                   #python 库
import urllib.request           #python3 使用 request 子模块

import re


def getHtml(url):
    page = urllib.request.urlopen(url)
    html = page.read()
    html = html.decode('utf-8')
    return html

def getHtml(url):
    page = urllib.request.urlopen(url)          #打开url
    html = page.read()                          #读取html全部  byte 
    #html =  page.readline()                     #读取html全部 byte 以列表形式
    #html =  page.readlines()
    html = html.decode('utf-8')                 #html byte 转换 string
    return html

def getImg(html):
    reg = r'src="(.+?\.jpg)" pic_ext'
    imgre = re.compile(reg)
    imglist = re.findall(imgre,html)       #html用decode(‘utf-8’)进行解码，由bytes变成string
    x = 0
    for imgurl in imglist:
        urllib.request.urlretrieve(imgurl,'D:\\work\\python\\爬虫\\PhotoSave\\%s.jpg' % x)
        x+=1

url = "http://tieba.baidu.com/p/2460150866"

#html = getHtml(url)              
#print (getImg(html))


#page = urllib.request.urlopen(url)   #返回http message
#info = page.info()
#print (info)

#page = urllib.request.urlopen(url)   #返回Http状态码。如果是http请求，200请求成功完成;404网址未找到
#getcode = page.getcode()
#print (getcode)

page = urllib.request.urlopen(url)   #返回请求的url
geturl = page.geturl()
print (geturl)