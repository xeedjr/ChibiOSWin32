#include <sstream>

#define _USE_WIHTTP_INTERFACE

#include "./restclient-cpp/textconv_helper.hpp"
#include "./restclient-cpp/restclient.hpp"

#include "Rest.h"
#include <nlohmann/json.hpp>
// for convenience
using namespace std;
using json = nlohmann::json;

std::string UUID_("64240aa3-a1d2-4357-9f8e-3ec8003faad4");
std::string ServerAddr("http://192.168.56.105:8085");

void connect_() {
	setlocale(LC_ALL, "US");

	RestClient::Response r;
	RestClient::Request request;

	request.timeout = 0;
	request.followRedirects = false;
	request.headers["User-Agent"] = "Mozilla/5.0";
	request.headers["Cookies"] = "name=value;";

	r = RestClient::get(ServerAddr + "/listUsers", &request);
	std::wstring body(textconv_helper::A2W_(r.body.c_str(), CP_UTF8));
	wprintf(L"body = %s \n", body.c_str());
}

void getInterrupt() {
	RestClient::Response r;
	RestClient::Request request;

	request.timeout = 60 * 60 * 1000; //60 min
	request.followRedirects = false;
	request.headers["User-Agent"] = "Mozilla/5.0";
	request.headers["Cookies"] = "name=value;";

	r = RestClient::get(ServerAddr + "/target/interrupt?targetId="+UUID_, &request);
	std::wstring body(textconv_helper::A2W_(r.body.c_str(), CP_UTF8));
	wprintf(L"body = %s \n", body.c_str());
}

void initObjectModule(void* moduleAddr, char* moduleName) {

}

json Get_command(std::string modName, void* moduleAddr) {
	RestClient::Response r;
	RestClient::Request request;

	request.timeout = 0;
	request.followRedirects = false;
	request.headers["User-Agent"] = "Mozilla/5.0";
	request.headers["Cookies"] = "name=value;";

	std::ostringstream url;
	url << ServerAddr << "/target/" << "?targetId=" << UUID_ << "&" << "modName=" << modName;

	r = RestClient::get(url.str(), &request);
	auto ans = json::parse(r.body);
	return ans;
}

json Post_command(std::string modName, void* moduleAddr, json module) {
	RestClient::Response r;
	RestClient::Request request;
	json ans;

	request.timeout = 0;
	request.followRedirects = false;
	request.headers["User-Agent"] = "Mozilla/5.0";
	request.headers["Cookies"] = "name=value;";

	std::string js = module.dump();

	std::ostringstream url;
	url << ServerAddr << "/target/" << "?targetId=" << UUID_ << "&" << "modName=" << modName;

	r = RestClient::post(url.str(), "application/json; charset=utf-8", js, &request);
	if (r.body.length() != 0) {
		ans = json::parse(r.body);
	};
	return ans;
}

void startObjectModule(void* moduleAddr, char* moduleName) {
/*	RestClient::Response r;
	RestClient::Request request;

	request.timeout = 0;
	request.followRedirects = false;
	request.headers["User-Agent"] = "Mozilla/5.0";
	request.headers["Cookies"] = "name=value;";

	// create an empty structure (null)
	json j;

	// add a number that is stored as double (note the implicit conversion of j to an object)
	j["targetId"] = UUID_;
	j["moduleId"] = (uint64_t)moduleAddr;
	j["moduleName"] = moduleName;
	
	std::string js = j.dump();;

	r = RestClient::post(ServerAddr + "/target", "application/json; charset=utf-8", js, &request);
	std::wstring body(textconv_helper::A2W_(r.body.c_str(), CP_UTF8));
	wprintf(L"body = %s \n", body.c_str());
	*/
}

/*-------------*/
uint8_t Rest_pal_lld_readport(void* port) {
	json j;
	j["operation"] = "readport";
	j = Post_command("PAL", port, j);
	return j["pad"].get<int>();
}
uint8_t Rest_pal_lld_readlatch(void* port) {
	json j;
	j["operation"] = "readlatch";
	j = Post_command("PAL", port, j);
	return j["pad"].get<int>();
}
void Rest_pal_lld_writeport(void* port, uint32_t bits) {
	json j;
	j["operation"] = "writeport";
	j["bits"] = bits;
	Post_command("PAL", port, j);
}
void Rest_pal_lld_setpad(void* port, uint8_t pad) {
	json j;
	j["operation"] = "setpad";
	j["pad"] = pad;
	Post_command("PAL", port, j);
}
void Rest_pal_lld_clearpad(void* port, uint8_t pad) {
	json j;
	j["operation"] = "clearpad";
	j["pad"] = pad;
	Post_command("PAL", port, j);
}