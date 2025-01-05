
**MVC** (모델-뷰-컨트롤러) 는 사용자 인터페이스, 데이터 및 논리 제어를 구현하는데 널리 사용되는 소프트웨어 디자인 패턴이다

비지니스 로직과 화면을 구분하는 관심사 분리에 초점을 맞춘 패턴이다

1. 모델: 데이터와 비즈니스 로직을 관리합니다.
2. 뷰: 레이아웃과 화면을 처리합니다.
3. 컨트롤러: 모델과 뷰로 명령을 전달합니다.

![img](https://developer.mozilla.org/ko/docs/Glossary/MVC/model-view-controller-light-blue.png)
### 모델
앱이 포함해야할 데이터를 정의한다.
데이터가 변경되면 뷰에 알림

### 뷰
앱의 데이터를 보여주는 방식을 정의한다.

### 컨트롤러
앱의 사용자들로부터 입력에 대한 응답으로 모델, 뷰를 업데이트하는 로직을 포함한다.

즉 로직을 컨트롤러에서 작성한다

### mvc 패턴 예시

```java
class Student
{
	private String rollNo;
	private String name;
	
	public String getRollNo()
	{
		return rollNo;
	}
	
	public void setRollNo(String rollNo)
	{
		this.rollNo = rollNo;
	}
	
	public String getName()
	{
		return name;
	}
	
	public void setName(String name)
	{
		this.name = name;
	}
}

class StudentView
{
	public void printStudentDetails(String studentName, String studentRollNo)
	{
		System.out.println("Student: ");
		System.out.println("Name: " + studentName);
		System.out.println("Roll No: " + studentRollNo);
	}
}

class StudentController
{
	private Student model;
	private StudentView view;

	public StudentController(Student model, StudentView view)
	{
		this.model = model;
		this.view = view;
	}

	public void setStudentName(String name)
	{
		model.setName(name);	
	}

	public String getStudentName()
	{
		return model.getName();	
	}

	public void setStudentRollNo(String rollNo)
	{
		model.setRollNo(rollNo);	
	}

	public String getStudentRollNo()
	{
		return model.getRollNo();	
	}

	public void updateView()
	{			
		view.printStudentDetails(model.getName(), model.getRollNo());
	}
}

class MVCPattern
{
	public static void main(String[] args)
	{
		Student model = retriveStudentFromDatabase();

		StudentView view = new StudentView();

		StudentController controller = new StudentController(model, view);

		controller.updateView();

		controller.setStudentName("Vikram Sharma");

		controller.updateView();
	}

	private static Student retriveStudentFromDatabase()
	{
		Student student = new Student();
		student.setName("Lokesh Sharma");
		student.setRollNo("15UCS157");
		return student;
	}
	
}

```

### 장점

- 여러 개발자가 모델, 컨트롤러 및 뷰에 대해 동시에 작업 가능
- MVC를 사용하면 컨트롤러의 관련 작업을 논리적으로 그룹화 가능
- 특정 모델에 대한 보기도 함께 그룹화
- 모델에는 여러 뷰가 있을 수 있다
- 애플리케이션의 전체 구성 요소는 쉽게 관리할 수 있으며 애플리케이션이 제대로 작동하기 위해 서로 덜 의존한다

### 단점

- 프레임워크 탐색은 새로운 추상화 계층을 도입하고 사용자가 MVC의 분해 기준에 적응해야 하기 때문에 복잡할 수 있다
- MVC를 사용하는 개발자는 다양한 기술에 능숙해야 한다