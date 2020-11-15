Command = 'gcc -g -std=c99 -O -Werror -Wall -Wextra -pedantic -Wno-error=format -Wno-error=unused-variable'

def assert(condition)
    unless condition
        raise "Failed"
    end
end

def to_source_file(name)
    source_file = name.gsub(/\\/, File::SEPARATOR)

    if source_file !~ /^src/
        source_file = 'src' + File::SEPARATOR + source_file
    end

    if source_file !~ /\.c$/
        source_file += '.c'
    end

    # p source_file

    source_file
end

def test_file_from_source_file(source_file)
    file_name = source_file[/#{File::SEPARATOR}[^#{File::SEPARATOR}.]+/][1..-1]

    test_name = '_' + file_name
    while test_name =~ /_(.)/
        rep = $1.upcase
        test_name = test_name.sub(/_(.)/, rep)
    end
    test_name += 'Test'
    test_file = "tests#{File::SEPARATOR}#{test_name}"

    # p test_file

    test_file
end

if __FILE__ == $0

    source = ARGV[0]

    source_file = to_source_file(source)
    assert(File.exist?(source_file))

    test_file = test_file_from_source_file(source_file)  + '.c'
    assert(File.exist?(test_file))
    test_exe = test_file_from_source_file(source_file) + '.exe'

    includes = IO.readlines(source_file).
        find_all { |line| line =~ /^#include \"/ }.
        map { |include| include[10..-5] }.
        map { |name| to_source_file(name) }.
        find_all { |file| File.exist?(file) }

    if File.exist?(test_exe)
        puts "del #{test_exe}"
        File.delete(test_exe)
    end

    puts "#{Command} #{source_file} #{includes.join(' ')} #{test_file} -l cmocka -o #{test_exe}"
    puts `#{Command} #{source_file} #{includes.join(' ')} #{test_file} -l cmocka -o #{test_exe}`
    if $?.exitstatus != 0
        puts "FAILED #{$?.exitstatus}"
        exit($?.exitstatus)
    end

    puts "#{test_exe}"
    puts `#{test_exe}`
    if $?.exitstatus != 0
        puts "FAILED #{$?.exitstatus}"
        exit($?.exitstatus)
    end
end
