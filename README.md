2016.11.01:

     It seemed I have do sth wrong with git. I recovered it back. And it works now.


------------------------------------------------------------------------------------
************************************************************************************
------------------------------------------------------------------------------------
2016.10.21:
	I have translate some chinese into english, and some just removed for not nessary. I will finish this work asap.

	And I have learned sth: 
	
	1, database not inited, you have to init it by exec mysql client , the script lies in sql.script. And it need the mysql acount: root/123456 localhost
	2, when user register, the system will generate a number as ID for the user, just like QQ.
        3, If someone forget his id and passwd, he can get it back if he can answer the question he setted when register.

        It is hard to believe there are so many files in this  sample project. I wonder if there is a better design somewhere.


------------------------------------------------------------------------------------
************************************************************************************
------------------------------------------------------------------------------------

LAN instant messaging system mainly uses Qt technology and QtCreator development tool in this article. As a kind of C++ GUI application development framework for cross-platform, Qt is very popular in the Linux. Qt technology has become increasingly mature, and also got great performance. In addition, the system also involves Socket, MySQL, MVC, V4L2, FFmpeg and other related theories and technologies.
The LAN instant messaging system mainly achieved registration, login, friend management, instant messaging, group chat, message management, mail transfer, file transfer, shared space and so on. After a simple registration, users can log into the system. Users can add friends, groups and discussion groups to communicate with other online users. What's more, the server and clients will store message records in the files or databases by themselves, so users can manage local records and network records at any time. Of course, file and mail transfer also be realized in this system. Besides that, Users and groups have their unique shared spaces, users can access friends' spaces, members of the group can access the space of the group, and share files with other users in the space.(The video module has been deleted.)

See more, please visit http://blog.csdn.net/shuideyidi/article/details/38260513
