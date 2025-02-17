# Rust语言代码风格

&emsp;&emsp;这篇文档将会介绍DragonOS中的Rust语言代码风格。随着开发的进行，这些风格可能会发生变化，但是我们会尽量保持风格的一致性。

## 1. 命名

&emsp;&emsp;这部分基于Rust语言圣经中的[命名规范](https://course.rs/practice/naming.html)进行修改，本文未提及的部分，请参考Rust语言圣经中的[命名规范](https://course.rs/practice/naming.html)。

## 2. 格式

### 2.1 缩进

&emsp;&emsp;请在提交代码之前，使用`cargo fmt`命令对代码进行格式化。

### 2.2 函数返回值

&emsp;&emsp;尽管Rust可以返回函数的最后一行的语句的值，但是，这种方式会使代码的可读性变差。因此，我们推荐您在函数的最后一行使用`return`语句，而不是直接返回值。

```rust
// 不推荐
fn foo() -> i32 {
    1 + 2
}

// 推荐
fn foo() -> i32 {
    return 1 + 2;
}
```
### 2.3 错误处理

&emsp;&emsp;DragonOS采用返回Posix错误码作为**模块间错误处理**的方式。为了确保在模块之间，错误处理代码的一致性，我们推荐在发生错误的时候，返回`SystemError`类型，该类型表示posix错误码。这样做的优点尤其体现在跨模块调用函数时，可以直接返回通用的错误码，从而降低错误处理代码的耦合度。

```rust
// 函数跨越模块边界时（由其他模块调用当前函数），不推荐
fn foo() -> Result<(), CustomErr> {
    if 1 + 2 == 3 {
        return Ok(());
    } else {
        return Err(CustomErr::error);
    }
}

// 函数跨越模块边界时（由其他模块调用当前函数），推荐
fn foo() -> Result<(), SystemError> {
    if 1 + 2 == 3 {
        return Ok(());
    } else {
        return Err(SystemError::EINVAL);
    }
}
```

&emsp;&emsp;在**模块内部**，您既可以采用返回自定义错误enum的方式，也可以采用返回`SystemError`的方式。但是，我们推荐您在模块内部，采用返回自定义错误enum的方式，这样可以使错误处理代码更加清晰。

&emsp;&emsp;**TODO**: 将原有的使用i32作为错误码的代码，改为使用`SystemError`。

## 3. 注释

&emsp;&emsp;DragonOS的注释风格与Rust官方的不太一样，我们部分结合了Linux的注释风格。同时，我们推荐您在代码中加入尽可能多的有效注释，以便于其他人理解您的代码。并且，变量、函数等声明，遵守第一节中提到的命名规范，使其能够“自注释”。

### 3.1 函数注释

&emsp;&emsp;函数注释应该包含以下内容：

- 函数的功能
- 函数的参数
- 函数的返回值
- 函数的错误处理
- 函数的副作用或者其他的需要说明的内容

&emsp;&emsp;函数注释的格式如下：

```rust
/// @brief 函数的功能
/// 
/// 函数的详细描述
/// 
/// @param 参数1 参数1的说明
/// 
/// @param 参数2 参数2的说明
/// 
/// @return 返回值的说明
```

&emsp;&emsp;如果函数的返回值是`Result`类型，那么返回值应当这样进行解释：

```rust
/// @return Ok(返回值类型) 返回值的说明
/// 
/// @return Err(错误值类型) 错误的说明
```
