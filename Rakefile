require 'rake'
require 'rspec/core/rake_task'

RSpec::Core::RakeTask.new(:integration) do |t|
  t.pattern = "spec/**/*_spec.rb"
end

namespace :nginx do
  desc "NGINX Version"
  task :version do
    `build/nginx/sbin/nginx -version`
  end

  desc "Starts NGINX"
  task :start do
    `build/nginx/sbin/nginx`
    sleep 1
  end

  desc "Stops NGINX"
  task :stop do
    `build/nginx/sbin/nginx -s stop`
  end

  desc "Recompiles NGINX"
  task :compile do
    sh "script/2_compile.sh"
  end

  desc "Compiles Dynamic module NGINX"
  task :compile_module do
    sh "script/3_compile_dynamic_module.sh"
  end
end

desc "Bootstraps the local development environment"
task :bootstrap do
  unless Dir.exists?("build") and Dir.exists?("vendor")
    sh "script/1_install_nginx.sh"
  end
end

desc "Run the integration tests"
task :default => [:bootstrap, "nginx:start", :integration, "nginx:stop"]