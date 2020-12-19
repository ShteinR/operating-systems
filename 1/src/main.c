#include <stdlib.h>
#include <stdio.h>

#include "memory/memory.h"

int main(int argc, char **argv) {
  int error_code = M_ERR_OK;

  // �������� ��� ������ 500 ���� � ������ �������� �� 50 ����
  memory* memory = m_init(500, 50, &error_code);
  printf("Initiated paged memory of size 500 bytes with page size of 50 bytes\n");
  if (error_code != M_ERR_OK) abort();

  // writing to pages
  m_id page_1 = m_write(memory, "OS Pagination", 14, &error_code);
  if (error_code != M_ERR_OK) abort();

  m_id page_2 = m_write(memory, "821703 3-iy variant", 20, &error_code);
  if (error_code != M_ERR_OK) abort();

  m_id page_3 = m_write(memory, "Paginated memory allocator!", 28, &error_code);
  if (error_code != M_ERR_OK) abort();

  // reading into buffer from pages
  char buffer[50];

  m_read(page_1, buffer, &error_code);	// ��������� � ����� ������ ��������
  if (error_code != M_ERR_OK) abort();
  printf("%s\n", buffer);

  m_read(page_2, buffer, &error_code);
  if (error_code != M_ERR_OK) abort();
  printf("%s\n", buffer);

  m_read(page_3, buffer, &error_code);
  if (error_code != M_ERR_OK) abort();
  printf("%s\n\n", buffer);
  
  printf("rewriting second page with another data\n\n");	// ����� ����� ����������� ������ �������� ������ �������

  m_free(page_2, &error_code);	// ������ 2-� �������� 
  m_id page_22 = m_write(memory, "rewrite 2nd page", 17, &error_code);	// ����� � ��� ����� ������

  m_id link = memory->next;	// ��������� �� ���� ������ � ������� ��� �������� ������, � ������� ������ � ������ �������� ������
  while (link != NULL) {
	  buffer[0] = '\0';
	  m_read(link, buffer, &error_code);
	  printf("'%s' (filled %d/%d) -> ", buffer, link->dataSize, link->size);
	  link = link->next;
  };

  //free memory
  m_free(page_1, &error_code);
  if (error_code != M_ERR_OK) abort();

  m_free(page_2, &error_code);
  if (error_code != M_ERR_OK) abort();

  m_free(page_3, &error_code);
  if (error_code != M_ERR_OK) abort();
}
