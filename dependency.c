/*
 * dependency.c
 *
 * It implements a task scheduler with dependencies.
 * Every task can depends only from another one, not multiple dependencies is allowed
 *
 * A task has this members.
 * status - block by dependency, waiting to run
 * depends - the task that depends on
 *
 * When a task is complete all dependencies are unblocked, one of them is execute in the same thread
 * if there is no more dependencies to unblock then a waiting one is pick from the list.
 *
 * every running task is move to the end of the list
 * when list size reach zero then the running thread finish.
 *
 * if there is no any task to do then the thread must wait in a waiting queue until waiting task !=0
 * ones all task are done ( list size ==0) then waiting task get the value -1 to wakeup all waiting threads
 * and release all thread because list is empty.
 * spin lock have to be use to access the list
 *
 * any module which its dependency is not found on the list will take the highest
 *
 * Picking a new task.
 * Wake up all waiting task.
 * If number of waked up task != 1 the decrement and waiting += waked up
 * if (waiting) wake_up queue
 * if list empty return null
 * if waiting == 0 then pick one, waiting = len, signal queue
 *
 *	Main thread will start others threads and pick task from the list.
 *	if all task are waiting for end_idx then wait for all threads
 *
 *	task can be waiting on (0:l] , done e+1,
 *
 *	List holding nodes idx
 *
 *  |----------------|----------|------------|
 *  begin            waiting    running      done/end
 *
 *  if waiting == running then all task became ready
 *
 *  two tables are in use
 *  1 . task data
 *  2 . task index -
 *
 *  Created on: 16 Apr 2015
 *      Author: lester.crespo
 */

/**
 * at least one element has to be in the list in the position 0 that never executes
 */
struct task_data
{
	const char * name;
	void* ptr;
	unsigned waiting_for_idx; // 0 ready,  1:end_idx waiting , > end_idx : lowest priority
};

/**
 * wait on the queue until unlocked != 0 then pick a task
 * locked == running; unlock all remaining task and scheduler
 *
 * main thread wait for unlocked !=0 or waiting == running
 * threads end when waiting == 0
 * last thread is when running became 0
 */
struct depends_list
{
	unsigned locked_idx;	// last task waiting to be release
	unsigned running_idx;	// the last task running
	unsigned end_idx;		// last element on the list
	unsigned unlocked;		// how many task are ready for execution
	unsigned idx_list[100];	// for test purpose
};

struct depends_list depends;
struct task_data task[100];
unsigned max_task;

/**
 * Mark task as done and get
 * Get a task from the list for execution
 * 0 - no more task available
 */
unsigned TaskDone(unsigned prev_id = 0)
{
	unsigned i;
	// spin lock
	if (prev_id != 0)
	{
		for (i = depends.running_idx; i < depends.end_idx; ++i)
		{
			if (depends.idx_list[i] == prev_id)
			{
				// bring down a task to do
				--depends.running_idx;
				depends.idx_list[i] = depends.idx_list[depends.running_idx];
				break;
			}
		}
		// release all task that depends on the finished one and remember
		for (i = 0; i < depends.locked_idx; ++i)
		{
			if (task[depends.idx_list[i]].waiting_for_idx == prev_id)
			{
				task[depends.idx_list[i]].waiting_for_idx = 0;
				depends.unlocked++;
			}
		}
	}
	// pick a new task
	if (depends.unlocked)
	{
		for (i = 0; i < depends.locked_idx && task[depends.idx_list[i]].waiting_for_idx != 0; ++i)
		{
		}
		--depends.unlocked;
		--depends.locked_idx;
		prev_id = depends.idx_list[i];
		depends.idx_list[i] = depends.idx_list[depends.locked_idx];
		depends.idx_list[depends.locked_idx] = prev_id;
	}
	else
		prev_id = 0;
	// spin unlock
	return prev_id;
}

