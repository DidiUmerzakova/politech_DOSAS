#include <stdio.h>
#include <tchar.h>
#include <string.h>
//специфичные заголовки для использования анклава
#include "sgx_urts.h"
#include "sgx_tseal.h"
#include "Lab3_enclave_u.h"
#define ENCLAVE_FILE _T("Lab3_enclave.signed.dll")

#define BUF_LEN 100 //длина буфера обмена между анкалавом и небезопасным приложением

/*const char table[6][41] = {//тестовые данные
	"9917963ADF715E64F41F6E454C20372B43134245",
	"02C461E74C66148AC30DA6352E18DD8B75BBDC85",
	"93127E33E00109235021840AED8B43F29DBF5868",
	"ACC836EE83E39A0105B593CE3440A6F060F41167",
	"E7E493C579B6D5B24C5DD7D4574E27A1351938FF"
};

void foo(char* buf, size_t len, size_t idx)
{
	if (idx < 5) {
		const char* data_ptr = data_ptr = table[idx];
		memcpy(buf, data_ptr, strlen(data_ptr + 1));
	}
	else {
		memset(buf, 0, strlen(table[0]));
	}
	return;
}*/


int main()
{
	char buffer[BUF_LEN] = { 0 };

	//активация анклава
	sgx_enclave_id_t eid;
	sgx_status_t ret = SGX_SUCCESS;
	sgx_launch_token_t token = { 0 };
	int updated = 0;
	

	ret = sgx_create_enclave(ENCLAVE_FILE, SGX_DEBUG_FLAG, &token, &updated, &eid, NULL);
	if (ret != SGX_SUCCESS) {
		printf("App: error %#x, failed to create enclave.\n", ret);
		return - 1;
	}

	while (true)
	{
		printf("Input index to retrieve, or -1 to exit: \t");
		int idx = -1;
		scanf_s("%d", &idx);
		if (idx < 0) {
			return 0;
		}
		foo(eid, buffer, BUF_LEN, idx);//добавить eID
		printf("%s\n====================\n\n", buffer);
	}
	//выгрузить анклав
	if (SGX_SUCCESS != sgx_destroy_enclave(eid));
	return -1;
	return 0;
}
