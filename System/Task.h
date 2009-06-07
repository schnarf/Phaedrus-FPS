#ifndef _SYSTEM_TASK_H
#define _SYSTEM_TASK_H

#include "common.h"
#include <boost/thread/thread.hpp>

namespace System {

	class Kernel;

	class Task {
		friend class Kernel;
	public:
		Task( string strName, bool bOwnThread= true );
		~Task();
		
		//! Start the task (init)
		void Start();
		//! Stop the task (deinit)
		void Stop();
		//! Run the task (process messages and process)
		void Run();
		
		//! Post a message to the task
		void PostMessage( uint eMsg );
		
		//! Get the task's thread ID
		inline ThreadID GetThreadID() const { return m_idThread; }
		//! Get whether this runs in its own thread
		inline bool IsOwnThread() const { return m_bOwnThread; }
		
	protected:
		//! Called whenever the thread is started
		virtual void init()= 0;
		//! Called when the thread is killed
		virtual void deinit()= 0;
		//! The thread's main loop, should return
		virtual void process()= 0;
		//! The thread's message processing function
		virtual void processMessages()= 0;
		
		//! The message queue, should make this thread-safe
		deque<uint> m_msgQueue;
		
		//! Our task's name
		string m_strName;
		
		//! Our thread ID
		ThreadID m_idThread;
		
		//! Whether we execute in our own thread
		const bool m_bOwnThread;
	private:
		//! The boost thread
		boost::thread* m_pThread;
		//! Our wrapper main loop
		void mainLoop();
		//! Whether we're running
		bool m_bRunning;
	};

};

#endif
