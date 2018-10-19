#pragma once

#include <string>
#include <iostream>
#include "params.hpp"



using namespace std;
class custom_config
{
public:
	//static int gpuIndex = 0;
	//static string gpu = "nvidia";
	//static int httpPort = 8765;

	static bool replace(std::string& str, const std::string& from, const std::string& to) {
		size_t start_pos = str.find(from);
		if (start_pos == std::string::npos)
			return false;
		str.replace(start_pos, from.length(), to);
		return true;
	}

	static string getConfigString()
	{
		//todo: inject http port
		std::string str(R"({
"call_timeout" : 10,
"retry_time" : 30,
"giveup_limit" : 0,
"verbose_level" : 3,
"print_motd" : true,
"h_print_time" : 60,
"aes_override" : null,
"use_slow_memory" : "warn",
"tls_secure_algo" : true,
"daemon_mode" : false,
"flush_stdout" : false,
"output_file" : "",
"httpd_port" : 8765,
"http_login" : "",
"http_pass" : "",
"prefer_ipv4" : true,
}
	)");

		return str;
	}

	static string getNVIDIAConfigString()
	{
		//if (xmrstak::params::inst().gpuName != "nvidia")
		//	return "{}";

		//std::cout << "GPU INDEX :"<<xmrstak::params::inst().gpuIndex<<std::endl;

		//todo: put gpu index
		std::string settings = R"(
			{
			"gpu_threads_conf" :
			[
			{ "index" : $gpuIndex,
			"threads" : 20, "blocks" : 15,
			"bfactor" : 8, "bsleep" : 25,
			"affine_to_cpu" : false, "sync_mode" : 3,
			"mem_mode":0
			},

			]
			}
			)";
		replace(settings, "$gpuIndex", std::to_string(xmrstak::params::inst().gpuIndex));
		return settings;
	}
	static string getAMDConfigString()
	{
		//todo: put gpu index
		/*
		stringstream ss;
		ss <<  R"({
		"gpu_threads_conf" : [
		{ "index" : )"
		<< xmrstak::params::inst().gpuIndex <<
		R"(, "intensity" : 1000, "worksize" : 8, "affine_to_cpu" : false, "strided_index" : true, "mem_chunk" : 2, "comp_mode" : true },
		],
		"platform_index" : 0,
		})";

		return ss.str();
		*/
		std::string settings = R"({
	"gpu_threads_conf" : [
{ "index" : $gpuIndex, "intensity" : 1000, "worksize" : 8, "affine_to_cpu" : false, "strided_index" : true, "mem_chunk" : 2, "comp_mode" : true,"unroll":8 },
],
"platform_index" : 0,
})";

		replace(settings, "$gpuIndex", std::to_string(xmrstak::params::inst().gpuIndex));
		return settings;
	}
	static string getPoolConfigString()
	{
		// todo: inject pool properties
		//xmrstak::params::inst().poolURL
		/*
		return R"({
"pool_list" :
[
	{"pool_address" : "pool.supportxmr.com:3333", "wallet_address" : "43QGgipcHvNLBX3nunZLwVQpF6VbobmGcQKzXzQ5xMfJgzfRBzfXcJHX1tUHcKPm9bcjubrzKqTm69JbQSL4B3f6E3mNCbU", "rig_id" : "", "pool_password" : "x", "use_nicehash" : false, "use_tls" : false, "tls_fingerprint" : "", "pool_weight" : 1 },
],
"currency" : "monero7"
})";
		*/

		std::string settings = R"({
"pool_list" :
[
	{"pool_address" : "$poolUrl", "wallet_address" : "$walletId", "rig_id" : "$rigId", "pool_password" : "$password", "use_nicehash" : false, "use_tls" : false, "tls_fingerprint" : "", "pool_weight" : 1 },
],
"currency" : "monero7"
})";

		replace(settings, "$poolUrl", xmrstak::params::inst().poolURL);
		replace(settings, "$walletId", xmrstak::params::inst().poolUsername);
		replace(settings, "$password", xmrstak::params::inst().poolPasswd);
		replace(settings, "$rigId", xmrstak::params::inst().poolRigid);

		return settings;
	}

	static string getCPUConfigString();
};