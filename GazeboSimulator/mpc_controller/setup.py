import os
from glob import glob
from setuptools import setup

package_name = 'mpc_controller'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'launch'), glob('launch/*.py')),
        (os.path.join('share', package_name, 'params'), glob('params/*.yaml'))
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='rov',
    maintainer_email='rov@todo.todo',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
        'GUI = mpc_controller.GUI:main',
        'bluerov_mpc = mpc_controller.mpc_controller:main',
        'setpoint = mpc_controller.setpoint_publisher:main',
        ],
    },
)
