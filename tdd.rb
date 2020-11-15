require('lib/ansi_term')

def assert(condition, cause='')
    unless condition
        raise "Failed #{cause}"
    end
end

# values copied from make file
Src_dir = 'src'
Test_dir = 'tests'

Gcc = %w|
  gcc
    -g -std=c99 -O
    -Werror -Wall -Wextra -pedantic
    -Wno-error=format -Wno-error=unused-variable
    %s
    -l cmocka
    -o %s
  |.join(' ').strip

def norm(path)
    full_path = File.expand_path(path)
    # relative to working dir
    remove = Dir.pwd.length + 1
    relative_path = full_path[remove..-1]
    # normalise /
    relative_path.gsub(/\\/, File::SEPARATOR)
end

def to_source_file(name)
    # normalize separators
    source_file = name.gsub(/\\/, File::SEPARATOR)
    # drop leading ./
    source_file = source_file.sub(/^\.#{File::SEPARATOR}/, '')
    # add src/
    if source_file !~ /^#{Src_dir}/
        source_file = Src_dir + File::SEPARATOR + source_file
    end
    # add .c
    if source_file !~ /\.c$/
        source_file += '.c'
    end

    norm(source_file)
end

def test_file_from_source_file(source_file)
    assert(File.exist?(source_file))

    file_name = source_file[/#{File::SEPARATOR}[^#{File::SEPARATOR}\.]+\.c$/][1..-3]
    # replace snake case with camel case
    test_name = '_' + file_name
    while test_name =~ /_(.)/
        rep = $1.upcase
        test_name = test_name.sub(/_(.)/, rep)
    end
    test_name += 'Test'
    # add tests/
    test_file = "#{Test_dir}#{File::SEPARATOR}#{test_name}.c"

    norm(test_file)
end

def included_files(source_file)
    assert(File.exist?(source_file))

    IO.readlines(source_file).
      find_all { |line| line =~ /^#include \"/ }.
      map { |include| include[10..-5] }.
      map { |name| to_source_file(name) }.
      find_all { |file| File.exist?(file) }
end

def check_exit_status
    if $? and $?.exitstatus != 0
        status = $?.exitstatus
        Ansi.puts_with_color(Ansi::RED, "FAILED #{status}")
        exit(status)
    end
end

def run_command(command)
    puts
    Ansi.puts_with_color(Ansi::WHITE, command)

    if block_given?
        result = yield
        if result
            result.split(/\n/).each do |line|
                if line =~ /failed|error|failure/i
                    Ansi.puts_with_color(Ansi::RED, line)
                elsif line =~ /warning/i
                    Ansi.puts_with_color(Ansi::YELLOW, line)
                elsif line =~ /passed|ok/i
                    Ansi.puts_with_color(Ansi::GREEN, line)
                else
                    puts line
                end
            end
        end
        check_exit_status
    end
end

def clean(test_exe)
    if File.exist?(test_exe)
        run_command("del #{test_exe}") do
            File.delete(test_exe)
            assert(!File.exist?(test_exe))
        end
    end
end

def compile(to_compile, test_exe)
    command = sprintf(Gcc, to_compile.join(' '), test_exe)
    run_command(command) { `#{command} 2>&1` }
end

def run_tests(test_exe)
    assert(File.exist?(test_exe))
    command = "run #{test_exe}"
    run_command(command) { `"#{test_exe}" 2>&1` }

    File.delete(test_exe)
    assert(!File.exist?(test_exe))
end

if __FILE__ == $0

    source = ARGV[0]

    to_compile = []

    source_file = to_source_file(source)
    assert(File.exist?(source_file))
    to_compile << source_file

    to_compile += included_files(source_file)

    test_file = test_file_from_source_file(source_file)
    assert(File.exist?(test_file))
    to_compile << test_file

    to_compile += included_files(test_file)

    test_exe = test_file_from_source_file(source_file)[0..-3] + '.exe'

    clean(test_exe)
    compile(to_compile.uniq, test_exe)
    run_tests(test_exe)
end
