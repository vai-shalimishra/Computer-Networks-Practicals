//SELECTIVE REPEAT simulation

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
#define WS 5		//window size
#define N  14		//number of frames to be send, frames are 0,1,2...N-1

int sendToReceiver(int data, int correctAck)
{
	cout<<"Reciver: received data: "<<data<<", ack: "<<correctAck<<endl;
	if(rand()%3 == 0)
	{
		cout<<"Reciver: sending negative acknowledgemnt\n";
		return -1;					//negative
	}
	else
	{
		cout<<"Reciver: sending positive Acknowledgement\n";
		return correctAck;			//positive
	}
}

int main()
{
	//sender code
	int window[WS];
	int windowStart=1;

	while(windowStart<=N)
	{
		cout<<"sender: window start at: "<<windowStart<<endl;

		int i;
		//initialising the window
		//window[i] correspond to data (windowStart+i)
		//window[i]!=0, means corresponding frames not acknowledged
		for(i=0; i<WS; ++i)		
			window[i]=windowStart+i;

		do
		{
			for(i=0; i<WS && windowStart+i<=N; ++i)
			{
				if(window[i]!=0)
				{
					cout<<"Sender: Data Send: "<<windowStart+i<<endl;
					int ack= sendToReceiver(windowStart+i, i);
					cout<<"Sender: Acknowledgement Received: "<<ack<<endl;

					if(ack!=-1)
					{
						window[ack]=0;
					}
				}
			}

			/*trying to find the first unacknowledged frame*/
			for(i=0; i<WS; ++i)
			{
				if(window[i]!=0)	
					break;
			}
		} while(i!=WS && windowStart+i!=N+1);

		/*next window starts from the first unacknowledged frame*/
		windowStart+=WS;
	}
	return 0;
}
