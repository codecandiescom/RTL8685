
/*
 * $Id: stmem.c,v 1.1.1.1 2003/08/18 05:40:24 kaohj Exp $
 *
 * DEBUG: section 19    Store Memory Primitives
 * AUTHOR: Harvest Derived
 *
 * SQUID Internet Object Cache  http://squid.nlanr.net/Squid/
 * ----------------------------------------------------------
 *
 *  Squid is the result of efforts by numerous individuals from the
 *  Internet community.  Development is led by Duane Wessels of the
 *  National Laboratory for Applied Network Research and funded by the
 *  National Science Foundation.  Squid is Copyrighted (C) 1998 by
 *  the Regents of the University of California.  Please see the
 *  COPYRIGHT file for full details.  Squid incorporates software
 *  developed and/or copyrighted by other sources.  Please see the
 *  CREDITS file for full details.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111, USA.
 *
 */

#include "squid.h"

void
stmemFree(mem_hdr * mem)
{
    mem_node *p;
    while ((p = mem->head)) {
	mem->head = p->next;
	memFree(p->data, MEM_STMEM_BUF);
	store_mem_size -= SM_PAGE_SIZE;
	safe_free(p);
    }
    mem->head = mem->tail = NULL;
    mem->origin_offset = 0;
}

int
stmemFreeDataUpto(mem_hdr * mem, int target_offset)
{
    int current_offset = mem->origin_offset;
    mem_node *lastp;
    mem_node *p = mem->head;
    while (p && ((current_offset + p->len) <= target_offset)) {
	if (p == mem->tail) {
	    /* keep the last one to avoid change to other part of code */
	    mem->head = mem->tail;
	    mem->origin_offset = current_offset;
	    return current_offset;
	} else {
	    lastp = p;
	    p = p->next;
	    current_offset += lastp->len;
	    memFree(lastp->data, MEM_STMEM_BUF);
	    store_mem_size -= SM_PAGE_SIZE;
	    safe_free(lastp);
	}
    }
    mem->head = p;
    mem->origin_offset = current_offset;
    if (current_offset < target_offset) {
	/* there are still some data left. */
	return current_offset;
    }
    assert(current_offset == target_offset);
    return current_offset;
}

/* Append incoming data. */
void
stmemAppend(mem_hdr * mem, const char *data, int len)
{
    mem_node *p;
    int avail_len;
    int len_to_copy;
    debug(19, 6) ("memAppend: len %d\n", len);
    /* Does the last block still contain empty space? 
     * If so, fill out the block before dropping into the
     * allocation loop */
    if (mem->head && mem->tail && (mem->tail->len < SM_PAGE_SIZE)) {
	avail_len = SM_PAGE_SIZE - (mem->tail->len);
	len_to_copy = XMIN(avail_len, len);
	xmemcpy((mem->tail->data + mem->tail->len), data, len_to_copy);
	/* Adjust the ptr and len according to what was deposited in the page */
	data += len_to_copy;
	len -= len_to_copy;
	mem->tail->len += len_to_copy;
    }
    while (len > 0) {
	len_to_copy = XMIN(len, SM_PAGE_SIZE);
	p = xcalloc(1, sizeof(mem_node));
	p->next = NULL;
	p->len = len_to_copy;
	p->data = memAllocate(MEM_STMEM_BUF);
	store_mem_size += SM_PAGE_SIZE;
	xmemcpy(p->data, data, len_to_copy);
	if (!mem->head) {
	    /* The chain is empty */
	    mem->head = mem->tail = p;
	} else {
	    /* Append it to existing chain */
	    mem->tail->next = p;
	    mem->tail = p;
	}
	len -= len_to_copy;
	data += len_to_copy;
    }
}

ssize_t
stmemCopy(const mem_hdr * mem, off_t offset, char *buf, size_t size)
{
    mem_node *p = mem->head;
    off_t t_off = mem->origin_offset;
    size_t bytes_to_go = size;
    char *ptr_to_buf = NULL;
    int bytes_from_this_packet = 0;
    int bytes_into_this_packet = 0;
    debug(19, 6) ("memCopy: offset %d: size %d\n", (int) offset, size);
    if (p == NULL)
	return 0;
    assert(size > 0);
    /* Seek our way into store */
    while ((t_off + p->len) < offset) {
	t_off += p->len;
	if (!p->next) {
	    debug(19, 1) ("memCopy: p->next == NULL\n");
	    return 0;
	}
	assert(p->next);
	p = p->next;
    }
    /* Start copying begining with this block until
     * we're satiated */
    bytes_into_this_packet = offset - t_off;
    bytes_from_this_packet = XMIN(bytes_to_go, p->len - bytes_into_this_packet);
    xmemcpy(buf, p->data + bytes_into_this_packet, bytes_from_this_packet);
    bytes_to_go -= bytes_from_this_packet;
    ptr_to_buf = buf + bytes_from_this_packet;
    p = p->next;
    while (p && bytes_to_go > 0) {
	if (bytes_to_go > p->len) {
	    xmemcpy(ptr_to_buf, p->data, p->len);
	    ptr_to_buf += p->len;
	    bytes_to_go -= p->len;
	} else {
	    xmemcpy(ptr_to_buf, p->data, bytes_to_go);
	    bytes_to_go -= bytes_to_go;
	}
	p = p->next;
    }
    return size - bytes_to_go;
}
