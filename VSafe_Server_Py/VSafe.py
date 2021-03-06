from CServerSockt import *
import threading
from CMysql import *
HOST='127.0.0.1'    #服务器IP
PORT=1234


def threadProc(*args, **kwargs):
    # 数据库手动查询
    sql = CMysql()
    while True:
        print('1.手动查询\n2.手动操作')
        index = int(input())
        if type(index) != int:
            print('输入有误，请重新输入...')
            pass
        elif index == 1:
            result = sql.query("SELECT * from userinfo")
            if result != None:
                print(result[0])
        elif index == 2:
            result = sql.DML(input('请输入操作语句'))
            if result != None:
                print('操作成功')
        else:
            print('输入有误，请重新输入...')
            pass

def main():

    tc=threading.Thread(target=threadProc)
    tc.start()

    #启动服务器
    server=CServerSocket(HOST,PORT)

    #选择
    server.ChatSelect()

if __name__=='__main__':
    main()
