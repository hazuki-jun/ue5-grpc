// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class GoogleRPC : ModuleRules
{
	private string ThirdPartyDirectory => Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty/"));

	private string ThirdPartyLibrariesDirectory => Path.Combine(ThirdPartyDirectory, "libs/");

	public GoogleRPC(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				// ... add other public dependencies that you statically link with here ...
			});

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{ 
			PublicDefinitions.Add("_CRT_SECURE_NO_WARNINGS");

			bEnableUndefinedIdentifierWarnings = false;
			bEnableExceptions = true;
			
            bEnableUndefinedIdentifierWarnings = false;
			PublicDefinitions.Add("GOOGLE_PROTOBUF_NO_RTTI");
			PublicDefinitions.Add("GRPC_ALLOW_EXCEPTIONS=0");
			PublicDefinitions.Add("GPR_FORBID_UNREACHABLE_CODE");

			PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "./Proto"));
			PublicIncludePaths.Add(Path.Combine(ThirdPartyDirectory, "include"));

			PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "libprotobuf.lib"));
			
			PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "address_sorting.lib"));
	        PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "cares.lib"));
	        PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "upb.lib"));
	        
	        // grpc merged library
	        PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "grpc_core.lib"));
			// absl merged library
	        PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "absl_core.lib"));
	        
	        // PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "gpr.lib"));
	        // PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "grpc_unsecure.lib"));
	        // PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "grpc++_unsecure.lib"));
	        
	        // PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "absl_base.lib"));
	        // PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "absl_malloc_internal.lib"));
	        // PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "absl_raw_logging_internal.lib"));
	        // PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "absl_spinlock_wait.lib"));
	        // PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "absl_throw_delegate.lib"));
	        // PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "absl_time.lib"));
	        // PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "absl_time_zone.lib"));
	        // PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "absl_graphcycles_internal.lib"));
	        // PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "absl_synchronization.lib"));
	        // PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "absl_str_format_internal.lib"));
	        // PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "absl_strings.lib"));
	        // PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "absl_strings_internal.lib"));
	        // PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "absl_status.lib"));
	        // PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "absl_statusor.lib"));
	        // PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "absl_int128.lib"));
			// PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "absl_stacktrace.lib"));
			// PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "absl_symbolize.lib"));
         
	        // PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "absl_cord.lib"));
            // PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "absl_bad_optional_access.lib"));
            
	        // absl hash internal
	        // PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "absl_hash.lib"));
	        // PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "absl_city.lib"));
	        //
	        // // absl typs
	        
	        // PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "absl_bad_any_cast_impl.lib"));
	        // PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "absl_bad_variant_access.lib"));

	        // // absl random
	        // PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "absl_random_distributions.lib"));
	        // PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "absl_random_internal_distribution_test_util.lib"));
	        // PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "absl_random_internal_platform.lib"));
	        // PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "absl_random_internal_pool_urbg.lib"));
	        // PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "absl_random_internal_randen.lib"));
	        // PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "absl_random_internal_randen_hwaes.lib"));
	        // PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "absl_random_internal_randen_hwaes_impl.lib"));
	        // PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "absl_random_internal_randen_slow.lib"));
	        // PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "absl_random_internal_seed_material.lib"));
	        // PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "absl_random_seed_gen_exception.lib"));
	        // PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "absl_random_seed_sequences.lib"));
	        
	        AddEngineThirdPartyPrivateStaticDependencies(Target, "zlib");
		}
	}
}
