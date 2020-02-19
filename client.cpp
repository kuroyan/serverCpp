#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
  int sockfd;
  struct sockaddr_in addr;
           
  // ソケット生成
  if( (sockfd = socket( AF_INET, SOCK_STREAM, 0) ) < 0 ) {
    perror( "socket" );
  }
  // 送信先アドレス・ポート番号設定
  addr.sin_family = AF_INET;
  addr.sin_port = htons( 1234 );
  addr.sin_addr.s_addr = inet_addr( "127.0.0.1" );
                 
  // サーバ接続
  connect( sockfd, (struct sockaddr *)&addr, sizeof( struct sockaddr_in ) );

  //-- データ送信
  char send_str[10];
  char receive_str[10];

  for ( int i = 0; i< 10; i++ ){
    sprintf( send_str, "%d", i );
    printf( "send:%d\n", i );
    if( send( sockfd,send_str, 10, 0 ) < 0) {
      perror("send");
    }else{
       recv( sockfd, receive_str, 10, 0 );
       printf( "receive:%s\n", receive_str );
    }
    sleep( 1 );
  }

  //ソケットクローズ
  close( sockfd );
   
  return 0;
}
