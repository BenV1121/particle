#pragma once

#include "particles.h"

using namespace std;

class ObjectPool
{
	struct __intern
	{
		bool	 open; // if this index is open
		size_t	 next; // next index in this list
		particle data; // the actual data we are storing
	};

	__intern *m_data; // array of underlying raw data.
	size_t	  m_size;
	
	size_t openHead;
	size_t fillHead;

public:
	ObjectPool(size_t a_size) : m_size(a_size), openHead(0)
	{
		m_data = new __intern[m_size];

		for (size_t i = 0; i < m_size; ++i)
		{
			m_data[i].open = true;
			m_data[i].next = i + 1;
		}
	}
	class iterator //faux pointer
	{
		ObjectPool *m_ref;
		size_t      m_idx;

		friend class ObjectPool;

		//ONLY the object pool can properly construct an iterator

		iterator(ObjectPool * a_ref, size_t a_idx) : m_ref(a_ref), m_idx(a_idx) {}
	public:
		iterator() : m_ref(nullptr), m_idx(0) {}

		particle &operator* ()   { return  m_ref->m_data[m_idx].data; } // *this
		particle *operator->()   { return &m_ref->m_data[m_idx].data; } // this->

		const particle &operator* () const { return  m_ref->m_data[m_idx].data; } 
		const particle *operator->() const { return &m_ref->m_data[m_idx].data; } 

		iterator &operator++()   { m_idx = m_ref->m_data[m_idx].next; return *this; } // ++this
		iterator operator++(int) { auto that = *this; operator++(); return that; } // this++

		bool operator== (const iterator &O) const { return m_ref == O.m_ref && m_idx == O.m_idx; }
		bool operator!= (const iterator &O) const { return !operator==(O); }

		operator bool() const { m_ref != nullptr && m_idx < m_ref -> m_size && !m_ref->m_data[m_idx].open; }
	};
	
	iterator push(const particle &val = particle())
	{
		if (openHead >= m_size) return iterator();

		size_t idx = openHead;

		m_data[idx].data = val;
		m_data[idx].open = false;

		openHead = m_data[openHead].next;

		if (idx <= fillHead) // if we get inserted before the head, become head
		{
			m_data[idx].next = fillHead;
			fillHead = idx;
		}
		else // otherwise there MUST be something filled to our left
		{
			size_t left = idx;

			// this will be closed when the loop stops.
			while (m_data[--left].open);

			m_data[idx].next = m_data[left].next;
			m_data[left].next = idx;
		}
		return iterator(this, idx);
	}

	iterator pop(const iterator &it)
	{
		if (!(it && it.m_ref == this)) return iterator();

		size_t idx = it.m_idx;

		// if we are popping the closed head, we need to update the close list
		// if we are popping left of the vacant head, we need to update the vacant head
		// if there was a closed next pointing to this index we have to update it.

		m_data[idx].open = true;

		if (idx == fillHead)
			fillHead = m_data[idx].next;
		else
		{
			size_t left = idx;
			while (m_data[--left].open);

			m_data[left].next = m_data[idx].next;
		}

		if (idx < openHead)
		{
			m_data[idx].next = openHead;;
			openHead = idx;
		}
		else
		{
			size_t left = idx;
			while (m_data[--left].open);

			m_data[idx].next = m_data[left].next;
			m_data[left].next = idx;
		}	
		return it;
	}
};