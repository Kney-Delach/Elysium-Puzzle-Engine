/**
 * FILENAME		: StackUnitTests.cpp
 * Name			: Ori Lazar
 * Student ID	: b9061712
 * Date			: 14/10/2019
 * Description	: This is the unit test class for the custom stack implementation for Elysium, 
				  the file can be found at Elysium/Core/Model/DataStructures/Stack.h
 */
#include "pch.h"
#include "Core/Model/DataStructures/Stack.h"

using namespace Elysium::Model;

TEST(StackTests, CopyConstructorTest)
{
	Stack<unsigned> stack(5);
	Stack<unsigned>* pAnotherStack = &stack;
	stack.Push(1);
	Stack<unsigned> anotherStack(stack);
	ASSERT_EQ(stack.GetCapacity(), anotherStack.GetCapacity()) << "Capcity should be the same.";
	ASSERT_EQ(stack.GetSize(), anotherStack.GetSize()) << "Size should be the same.";
	ASSERT_EQ(stack.Top(), anotherStack.Top()) << "Element details should be an exact copy.";
	ASSERT_NE(&anotherStack.Top(), &(pAnotherStack->Top())) << "Element address shouldn't be an exact copy.";
	stack.Push(2);
	ASSERT_EQ(stack.GetCapacity(), anotherStack.GetCapacity()) << "Capcity should be the same.";
	ASSERT_NE(stack.GetSize(), anotherStack.GetSize()) << "Size should not be the same.";
	ASSERT_NE(stack.Top(), anotherStack.Top()) << "Element details should not be an exact copy.";
	ASSERT_NE(&anotherStack.Top(), &(pAnotherStack->Top())) << "Element address shouldn't be an exact copy.";
}

TEST(StackTests, AssignmentTest)
{
	Stack<unsigned> stack(5);
	Stack<unsigned> anotherStack(5);
	Stack<unsigned>* pAnotherStack = &anotherStack;
	stack.Push(1);
	stack.Push(2);
	anotherStack.Push(3);
	stack = anotherStack;
	ASSERT_EQ(stack.GetCapacity(), anotherStack.GetCapacity()) << "[Capacity Copy] Stack assignment operator failing.";
	ASSERT_EQ(stack.GetSize(), anotherStack.GetSize()) << "Size Copy.";
	ASSERT_EQ(stack.Top(), anotherStack.Top()) << "Element details should be completely copy.";
	ASSERT_NE(&stack.Top(), &(pAnotherStack->Top())) << "Element address shouldn't be an exact copy.";
}

TEST(StackTests, CapacityInitTest)
{
	Stack<unsigned>* stack = new Stack<unsigned>(1);
	ASSERT_EQ(stack->GetCapacity(), 1) << "Stack capacitance initialization failing.";
	ASSERT_NE(stack->GetCapacity(), 2) << "Stack capacitance initialization failing.";
	ASSERT_NE(stack->GetCapacity(), -1) << "Stack capacity shouldn't be negative.";
	delete stack;
}

TEST(StackTests, CpacityFullTest)
{
	Stack<unsigned> stack(1);
	stack.Push(1);
	stack.Push(2);
	ASSERT_EQ(stack.GetCapacity(), 1) << "Capacity shouldn't increase!";
	ASSERT_EQ(stack.GetSize(), 1) << "Size should be the same as max capacity.";
	ASSERT_EQ(stack.Top(), 1) << "Stack top should contain the most recent item added whilst the capacity wasn't full.";
}

TEST(StackTests, GetSizeTest)
{
	Stack<unsigned> stack(5);
	ASSERT_EQ(stack.GetSize(), 0) << "Stack should have size 0.";
	stack.Push(1);
	ASSERT_EQ(stack.GetSize(), 1) << "Stack should have size 1.";
	stack.Pop();
	ASSERT_EQ(stack.GetSize(), 0) << "Stack should have size 0.";
}

TEST(StackTests, IsEmptyTest)
{
	Stack<unsigned> stack(1);
	ASSERT_EQ(stack.IsEmpty(), true) << "Stack should be empty.";
	stack.Push(1);
	ASSERT_EQ(stack.IsEmpty(), false) << "Stack shouldn't be empty.";
	stack.Pop();
	ASSERT_EQ(stack.IsEmpty(), true) << "Stack should be empty.";
}