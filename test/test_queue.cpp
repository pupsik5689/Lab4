#include <gtest.h>
#include "Queue.h"

TEST(TQueue, can_create_queue_with_positive_length)
{
	ASSERT_NO_THROW(TQueue<int> q(5));
}

TEST(TQueue, cant_create_too_large_queue)
{
	ASSERT_ANY_THROW(TQueue<int> q(MAX_QUEUE_SIZE + 1));
}

TEST(TQueue, throws_when_create_queue_with_negative_length)
{
	ASSERT_ANY_THROW(TQueue<int> q(-1));
}

TEST(TQueue, can_create_copied_queue)
{
	TQueue<int> q(10);
	ASSERT_NO_THROW(TQueue<int> q1(q));
}

TEST(TQueue, copied_queue_is_equal_to_source_one)
{
	TQueue<int> q1(5);
	q1.Push(1);
	q1.Push(2);
	q1.Push(3);

	TQueue<int> q2(q1);
	EXPECT_EQ(true, q1 == q2);
}

TEST(TQueue, copied_queue_has_its_own_memory)
{
	TQueue<int> q1(5);
	for (int i = 0; i < 3; i++)
		q1.Push(i);

	TQueue<int> q2(q1);
	q2.Pop();
	q2.Push(5);
	EXPECT_EQ(true, q1 != q2);
}

TEST(TQueue, can_push_and_top_element)
{
	TQueue<int> q(5);
	q.Push(1);
	q.Push(2);
	EXPECT_EQ(1, q.Top());
}

TEST(TQueue, can_pop_element)
{
	TQueue<int> q(5);
	q.Push(1);
	q.Push(2);
	q.Pop();
	EXPECT_EQ(2, q.Top());
}

TEST(TQueue, empty_or_not)
{
	TQueue<int> q(5);
	EXPECT_EQ(true, q.IsEmpty());
	q.Push(1);
	EXPECT_EQ(false, q.IsEmpty());
	q.Pop();
	EXPECT_EQ(true, q.IsEmpty());
}

TEST(TQueue, full_or_not)
{
	TQueue<int> q(5);
	EXPECT_EQ(false, q.IsFull());
	q.Push(1);
	EXPECT_EQ(false, q.IsFull());
	for (int i = 1; i < 5; i++)
		q.Push(i * 2);
	EXPECT_EQ(true, q.IsFull());
}

TEST(TQueue, throws_when_push_in_full)
{
	TQueue<int> q(5);
	for (int i = 0; i < 5; i++)
		q.Push(i * 2);
	ASSERT_ANY_THROW(q.Push(0));
}

TEST(TQueue, throws_when_pop_in_empty)
{
	TQueue<int> q(5);
	q.Push(1);
	q.Pop();
	ASSERT_ANY_THROW(q.Pop());
}

TEST(TQueue, can_assign_queue_to_itself)
{
	TQueue<int> q(5);
	ASSERT_NO_THROW(q = q);
}

TEST(TQueue, compare_equal_queues_return_true)
{
	TQueue<int> q1(5), q2(5);
	q1.Push(5);
	q1.Push(6);
	q1.Push(7);

	q2.Push(5);
	q2.Push(6);
	q2.Push(7);
	EXPECT_EQ(true, q1 == q2);
}

TEST(TQueue, compare_queue_with_itself_return_true)
{
	TQueue<int> q(5);
	q.Push(0);
	EXPECT_EQ(true, q == q);
}

TEST(TQueue, queues_with_different_size_are_not_equal)
{
	TQueue<int> q1(5), q2(5);
	q1.Push(5);
	q1.Push(6);
	q2.Push(5);
	EXPECT_EQ(true, q1 != q2);
}

TEST(TQueue, test_queue_cercular_buffer)
{
	TQueue<int> q(4);
	q.Push(2);
	q.Push(3);
	q.Push(4);
	q.Push(5);
	EXPECT_EQ(true, q.IsFull());
	q.Pop();
	EXPECT_EQ(false, q.IsFull());
	ASSERT_NO_THROW(q.Push(6));
	q.Pop();
	ASSERT_NO_THROW(q.Push(7));
	EXPECT_EQ(4, q.TopPop());
	EXPECT_EQ(5, q.TopPop());
	EXPECT_EQ(6, q.TopPop());
	EXPECT_EQ(7, q.TopPop());
	EXPECT_EQ(true, q.IsEmpty());
}